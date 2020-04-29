#pragma once

#include <thread>
#include <WinSock2.h>
#include "IpAddress.h"

class StreamingSocket
{
	static int ID;
	int mID;
	SOCKET mSocket;
	std::thread mConnection;
	bool mClose = false;

public:
	StreamingSocket(const IpAddress & pAddress);
	~StreamingSocket();

	StreamingSocket(const StreamingSocket&) = delete;
	StreamingSocket(StreamingSocket&&) = delete;
	StreamingSocket& operator= (const StreamingSocket&) = delete;
	StreamingSocket& operator= (StreamingSocket&&) = delete;

	void Send(const std::string & pMessage);
	void Recieve();
	
	void CloseConnection(bool pFullClose = true);
};

