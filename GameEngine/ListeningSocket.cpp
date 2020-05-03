#include "ListeningSocket.h"


#include <iomanip>
#include <iostream>
#include <sstream>

#include "ServerNetworkingManager.h"

int ListeningSocket::ID = 0;

ListeningSocket::ListeningSocket(const SOCKET & pSocket) : mSocket(pSocket), mID(ID)
{
	std::cout << "Connection Started With ID " << mID << std::endl;

	mConnection = std::thread(&ListeningSocket::Recieve, this);
	ID++;
}

ListeningSocket::~ListeningSocket()
{
	//TODO: Better way of joining 
	mConnection.detach();
}

void ListeningSocket::Recieve()
{
	while (true)
	{
		char buffer[11] = "";
		if (recv(mSocket, buffer, 10, 0) == SOCKET_ERROR)
		{
			if (mClose)
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
			char tempBuffer[11] = "";
			int left = size - message.size();
			left = left > 10 ? 10 : left;

			if (recv(mSocket, tempBuffer, left, 0) == SOCKET_ERROR)
			{
				if (mClose)
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

		Send(message);
	}
}


void ListeningSocket::Send(const std::string& pMessage)
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
		if (mClose)
		{
			return;
		}

		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;

		CloseConnection(false);
	}

	std::cout << "Connection " << mID << " Send Message " << pMessage << std::endl;
}

void ListeningSocket::CloseConnection(const bool pFullClose)
{
	mClose = true;

	if (pFullClose)
	{
		Send("q");
	}

	std::cout << "Connection Ended With ID " << mID << std::endl;

	closesocket(mSocket);

	ServerNetworkingManager::Instance()->RemoveConnection(this);
}
