#include <iostream>
#include <WinSock2.h>

#include "IpAddress.h"
#include "StreamingSocket.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
	IpAddress address(7500, "127.0.0.1");

	StreamingSocket socket(address);

	std::string c;

	while(std::cin >> c, c != "q")
	{
		socket.Send(c);
	}

	socket.CloseConnection();
}