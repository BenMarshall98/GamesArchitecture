#include <iostream>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "IpAddress.h"
#include "ListeningSocket.h"

#pragma comment(lib, "ws2_32.lib")

ListeningSocket serverSocket;

void threadMain()
{
	IpAddress address(7500);
	serverSocket.StartListening(address, [](const SOCKET & pSocket)
	{
		char buffer;
		if (pSocket == INVALID_SOCKET)
		{
			std::cerr << "Accept failed with " << WSAGetLastError() << std::endl;
		}
		else if (recv(pSocket, &buffer, 1, 0) == SOCKET_ERROR)
		{
			std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;
		}
		else
		{
			std::cout << "Message = " << buffer << std::endl;

			if (send(pSocket, "2", 1, 0) == SOCKET_ERROR)
			{
				std::cerr << "Send failed with " << WSAGetLastError() << std::endl;
			}
		}
		closesocket(pSocket);
	});
}

int main()
{
	std::thread server(threadMain);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	serverSocket.CloseServer();

	if (server.joinable())
	{
		server.join();
	}

	system("PAUSE");
}