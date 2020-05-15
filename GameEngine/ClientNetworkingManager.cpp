#include "ClientNetworkingManager.h"

#include <iomanip>
#include <iostream>
#include <sstream>

ClientNetworkingManager * ClientNetworkingManager::mInstance = nullptr;

ClientNetworkingManager::ClientNetworkingManager()
{
	auto versionRequested = MAKEWORD(2, 0);

	WSADATA wsaData;

	if (WSAStartup(versionRequested, &wsaData))
	{
		std::cerr << "Socket initialisation failed" << std::endl;
		return;
	}
}

bool ClientNetworkingManager::StartListening(const IpAddress& pAddress)
{
	char buffer;
	mSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (mSocket == INVALID_SOCKET)
	{
		std::cerr << "Create socket failed" << std::endl;
		return false;
	}
	if (connect(mSocket, (sockaddr *)&pAddress.GetPeer(), sizeof(pAddress.GetPeer())) == SOCKET_ERROR)
	{
		std::cerr << "Connect to peer failed with " << WSAGetLastError() << std::endl;
		return false;
	}

	const auto recieveFunction = [this](ThreadTask * pThread)
	{
		while (true)
		{
			char buffer[11] = "";
			if (recv(mSocket, buffer, 10, 0) == SOCKET_ERROR)
			{
				if (pThread->GetClose())
				{
					return;
				}

				std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;

				CloseConnection(false);

				break;
			}

			std::string message = buffer;

			std::istringstream str(message.substr(0, 4));

			int size;
			str >> size;

			str = std::istringstream(message.substr(4, 4));

			int checksum;
			str >> checksum;

			message = message.erase(0, 8);

			size -= 8;

			while (message.size() != size)
			{
				char tempBuffer[101] = "";
				int left = size - message.size();
				left = left > 100 ? 100 : left;

				if (recv(mSocket, tempBuffer, left, 0) == SOCKET_ERROR)
				{
					if (pThread->GetClose())
					{
						break;
					}

					std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;

					CloseConnection(false);

					return;
				}

				message += tempBuffer;
			}

			auto checking = 0u;

			for (int i = 0; i < message.size(); i++)
			{
				checking += static_cast<int>(message[i]);
			}

			if (checksum != checking % 10000)
			{
				std::cerr << "Checksum failed " << std::endl;
				break;
			}

			if (message == "q")
			{
				CloseConnection(false);
			}

			if (!mRecieveMessageFunction(message))
			{
				AddRecieveMessage(message);
			}
		}
	};

	const auto sendFunction = [this](ThreadTask * pThread)
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mSendMutex);
			mSendConditionVariable.wait(lock, [this] {return !mSendMessages.empty(); });

			const auto message = mSendMessages[0];
			mSendMessages.erase(mSendMessages.begin());

			lock.unlock();

			Process(message);

			if (pThread->GetClose())
			{
				return;
			}
		}
	};
	
	mRecieveConnection.Run(recieveFunction);
	mSendConnection.Run(sendFunction);
	return true;
}

ClientNetworkingManager::~ClientNetworkingManager()
{
	mRecieveConnection.Close();
	mSendConnection.Close();
	closesocket(mSocket);
}

void ClientNetworkingManager::Process(const std::string & pMessage)
{
	int size = pMessage.size() + 8;

	std::ostringstream str;

	str << std::setfill('0') << std::setw(4) << size;

	auto checksum = 0u;

	for (int i = 0; i < pMessage.size(); i++)
	{
		checksum += static_cast<int>(pMessage[i]);
	}

	str << std::setfill('0') << std::setw(4) << checksum % 10000;

	str << pMessage;

	auto message = str.str();

	if (send(mSocket, str.str().c_str(), size, 0) == SOCKET_ERROR)
	{
		if (mSendConnection.GetClose())
		{
			return;
		}

		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;

		CloseConnection(false);
	}
}

//Based on https://freecontent.manning.com/synchronizing-concurrent-operations-in-c/

void ClientNetworkingManager::AddSendMessage(const std::string& pMessage)
{
	std::lock_guard<std::mutex> lock(mSendMutex);

	mSendMessages.push_back(pMessage);

	mSendConditionVariable.notify_one();
}

void ClientNetworkingManager::CloseConnection(const bool pFullClose)
{
	mSendConnection.Close();
	mRecieveConnection.Close();
	
	if (pFullClose)
	{
		AddSendMessage("q");
	}

	closesocket(mSocket);
}