#include "ListeningSocket.h"


#include <iomanip>
#include <iostream>
#include <sstream>

#include "ServerNetworkingManager.h"

int ListeningSocket::ID = 0;

ListeningSocket::ListeningSocket(const SOCKET & pSocket) : mSocket(pSocket), mID(ID)
{
	std::cout << "Connection Started With ID " << mID << std::endl;

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

			if (size > 20)
			{
				int i = 0;
			}

			while (message.size() != size)
			{
				char tempBuffer[11] = "";
				int left = size - message.size();
				left = left > 10 ? 10 : left;

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

			std::cout << "Connection " << mID << " Received Message " << message << std::endl;

			if (message == "q")
			{
				CloseConnection(false);
			}

			ServerNetworkingManager::Instance()->AddRecieveMessage(message);
		}
	};

	const auto sendFunction = [this](ThreadTask * pThread)
	{
		while (true)
		{
			//TODO: Deal with adding a delay
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
	ID++;
}

ListeningSocket::~ListeningSocket()
{
	mRecieveConnection.Close();
	mSendConnection.Close();
}

void ListeningSocket::Process(const std::string& pMessage)
{
	const auto size = pMessage.size() + 8u;

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

	std::cout << "Connection " << mID << " Send Message " << pMessage << std::endl;
}

void ListeningSocket::AddSendMessage(const std::string& pMessage)
{
	std::lock_guard<std::mutex> lock(mSendMutex);

	mSendMessages.push_back(pMessage);

	mSendConditionVariable.notify_one();
}

void ListeningSocket::CloseConnection(const bool pFullClose)
{
	mSendConnection.Close();
	mRecieveConnection.Close();
	
	if (pFullClose)
	{
		Process("q");
	}

	std::cout << "Connection Ended With ID " << mID << std::endl;

	closesocket(mSocket);

	ServerNetworkingManager::Instance()->RemoveConnection(this);
}