#pragma once

#include <functional>
#include <thread>
#include <WinSock2.h>
#include "IpAddress.h"

class ListeningSocket
{
	static int ID;
	int mID;
	SOCKET mSocket;
	std::thread mConnection;
	bool mClose = false;

public:
	ListeningSocket(const SOCKET & pSocket);
	~ListeningSocket();

	ListeningSocket(const ListeningSocket&) = delete;
	ListeningSocket(ListeningSocket&&) = delete;
	ListeningSocket& operator= (const ListeningSocket&) = delete;
	ListeningSocket& operator= (ListeningSocket&&) = delete;

	void Send(const std::string & pMessage);
	void Recieve();
	
	void CloseConnection(bool pFullClose = true);
};

