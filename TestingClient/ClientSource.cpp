#include <iostream>
#include <WinSock2.h>

#include "IpAddress.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
	auto versionRequested = MAKEWORD(2, 0);

	WSADATA wsaData;

	if (WSAStartup(versionRequested, &wsaData))
	{
		std::cerr << "Socket initialisation failed" << std::endl;
		return -1;
	}

	IpAddress address(7500, "127.0.0.1");

	char buffer;
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	
	if (s == INVALID_SOCKET)
	{
		std::cerr << "Create socket failed" << std::endl;
	}
	else if (connect(s, (sockaddr *)&address.GetPeer(), sizeof(address.GetPeer())) == SOCKET_ERROR)
	{
		std::cerr << "Connect to peer failed with " << WSAGetLastError() << std::endl;
	}
	else if (send(s, "1", 1, 0) == SOCKET_ERROR)
	{
		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;
	}
	else if (recv(s, &buffer, 1, 0) == SOCKET_ERROR)
	{
		std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "Message = " << buffer << std::endl;
	}

	WSACleanup();
}