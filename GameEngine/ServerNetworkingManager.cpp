#include "ServerNetworkingManager.h"

#include <iostream>

ServerNetworkingManager * ServerNetworkingManager::mInstance = nullptr;

ServerNetworkingManager::ServerNetworkingManager()
{
	const auto versionRequested = MAKEWORD(2, 0);

	WSADATA wsaData;

	if (WSAStartup(versionRequested, &wsaData))
	{
		std::cerr << "Socket initialization failed" << std::endl;
	}
}

ServerNetworkingManager::~ServerNetworkingManager()
{
	//TODO: Better way of joining / detaching thread
	mConnection.detach();
	WSACleanup();
}

bool ServerNetworkingManager::StartListening(const IpAddress& pAddress)
{
	mSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocket == INVALID_SOCKET)
	{
		std::cerr << "Create socket failed" << std::endl;
		return false;
	}

	if (bind(mSocket, (sockaddr *)&pAddress.GetPeer(), sizeof(pAddress.GetPeer())) == SOCKET_ERROR)
	{
		std::cerr << "Bind failed with " << WSAGetLastError() << std::endl;
		return false;
	}

	if (listen(mSocket, 5) == SOCKET_ERROR)
	{
		std::cerr << "Listen failed with " << WSAGetLastError() << std::endl;
		return false;
	}

	std::cout << "Started Listening" << std::endl;

	mConnection = std::thread(&ServerNetworkingManager::Connect, this);
	return true;
}

void ServerNetworkingManager::Connect()
{
	while (true)
	{
		const auto socket = accept(mSocket, nullptr, nullptr);

		if (mClose)
		{
			break;
		}

		std::cout << "Socket Accepted " << std::endl;

		std::lock_guard<std::mutex> lock(mListeningMutex);

		const auto listeningSocket = std::make_shared<ListeningSocket>(socket);
		mListeningSockets.push_back(listeningSocket);
	}
}

void ServerNetworkingManager::RemoveConnection(ListeningSocket* pListeningSocket)
{
	std::lock_guard<std::mutex> lock(mListeningMutex);
	
	for (int i = 0; i < mListeningSockets.size(); i++)
	{
		if (mListeningSockets[i].get() == pListeningSocket)
		{
			mListeningSockets.erase(mListeningSockets.begin() + i);
			return;
		}
	}
}

void ServerNetworkingManager::CloseServer()
{
	mClose = true;

	for (int i = 0; i < mListeningSockets.size(); i++)
	{
		mListeningSockets[i]->CloseConnection();
	}

	closesocket(mSocket);
}

void ServerNetworkingManager::AddSendMessage(const std::string& pMessage)
{
	std::lock_guard<std::mutex> lock(mListeningMutex);

	for (int i = 0; i < mListeningSockets.size(); i++)
	{
		mListeningSockets[i]->AddSendMessage(pMessage);
	}
}
