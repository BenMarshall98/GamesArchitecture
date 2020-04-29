#include "NetworkingManager.h"

#include <iostream>

NetworkingManager * NetworkingManager::mInstance = nullptr;

NetworkingManager::NetworkingManager() : mSocket()
{
	const auto versionRequested = MAKEWORD(2, 0);

	WSADATA wsaData;

	if (WSAStartup(versionRequested, &wsaData))
	{
		std::cerr << "Socket initialization failed" << std::endl;
	}
}

NetworkingManager::~NetworkingManager()
{
	WSACleanup();
}

bool NetworkingManager::StartListening(const IpAddress& pAddress)
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

	while (true)
	{
		const auto socket = accept(mSocket, nullptr, nullptr);

		if (mClose)
		{
			break;
		}

		std::cout << "Socket Accepted " << std::endl;

		const auto listeningSocket = std::make_shared<ListeningSocket>(socket);
		mListeningSockets.push_back(listeningSocket);
	}
}

void NetworkingManager::RemoveConnection(ListeningSocket* pListeningSocket)
{
	for (int i = 0; i < mListeningSockets.size(); i++)
	{
		if (mListeningSockets[i].get() == pListeningSocket)
		{
			mListeningSockets.erase(mListeningSockets.begin() + i);
			return;
		}
	}
}

void NetworkingManager::CloseServer()
{
	mClose = true;

	for (int i = 0; i < mListeningSockets.size(); i++)
	{
		mListeningSockets[i]->CloseConnection();
	}

	closesocket(mSocket);
}