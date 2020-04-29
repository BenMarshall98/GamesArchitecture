#include "ListeningSocket.h"

#include <iostream>

ListeningSocket::ListeningSocket(const SOCKET & pSocket) : mSocket(pSocket)
{
}

ListeningSocket::~ListeningSocket()
{
}

bool ListeningSocket::StartListening(const IpAddress& pAddress, const std::function<void(const SOCKET & pS)> & pFunction)
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
	
	while (true)
	{
		const auto socket = accept(mSocket, nullptr, nullptr);

		if (mClose)
		{
			break;
		}

		std::cout << "Socket Accepted " << std::endl;

		pFunction(socket);
	}

	return true;
}