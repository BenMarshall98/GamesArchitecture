#pragma once

#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
#include <WinSock2.h>
#include "IpAddress.h"

class ListeningSocket
{
	static int ID;
	int mID;

	std::mutex mSendMutex;
	std::condition_variable mSendConditionVariable;
	std::vector<std::string> mSendMessages;
	
	SOCKET mSocket;
	std::thread mRecieveConnection;
	std::thread mSendConnection;
	
	bool mClose = false;

public:
	explicit ListeningSocket(const SOCKET & pSocket);
	~ListeningSocket();

	ListeningSocket(const ListeningSocket&) = delete;
	ListeningSocket(ListeningSocket&&) = delete;
	ListeningSocket& operator= (const ListeningSocket&) = delete;
	ListeningSocket& operator= (ListeningSocket&&) = delete;

	void Send();
	void Process(const std::string & pMessage);
	void Recieve();

	void CloseConnection(bool pFullClose = true);
	void AddSendMessage(const std::string & pMessage);
};

