#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "IpAddress.h"
#include "ListeningSocket.h"
#include "NetworkingManager.h"

#pragma comment(lib, "ws2_32.lib")

void threadMain()
{
	IpAddress address(7500);

	NetworkingManager::Instance()->StartListening(address);
}

int main()
{
	std::thread server(threadMain);

	char c = ' ';

	while (c != 'q')
	{
		std::cout << "Please enter 'q' to close server " << std::endl;

		std::cin >> c;
	}

	NetworkingManager::Instance()->CloseServer();

	if (server.joinable())
	{
		server.join();
	}

	system("PAUSE");
}