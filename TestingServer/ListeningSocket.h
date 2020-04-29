#pragma once

#include <functional>
#include <WinSock2.h>
#include "IpAddress.h"

class ListeningSocket
{
	SOCKET mSocket;
	bool mClose = false;

public:
	ListeningSocket(const SOCKET & pSocket);
	~ListeningSocket();

	ListeningSocket(const ListeningSocket&) = delete;
	ListeningSocket(ListeningSocket&&) = delete;
	ListeningSocket& operator= (const ListeningSocket&) = delete;
	ListeningSocket& operator= (ListeningSocket&&) = delete;

	void 
	
	void CloseConnection();
};

