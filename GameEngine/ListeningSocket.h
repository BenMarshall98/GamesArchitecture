#pragma once

#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
#include <WinSock2.h>
#include "IpAddress.h"
#include "ThreadTask.h"

class ListeningSocket
{
	static int ID;
	int mID;

	std::mutex mSendMutex;
	std::condition_variable mSendConditionVariable;
	std::vector<std::string> mSendMessages;
	
	SOCKET mSocket;
	ThreadTask mRecieveConnection;
	ThreadTask mSendConnection;

public:
	explicit ListeningSocket(const SOCKET & pSocket);
	~ListeningSocket();

	ListeningSocket(const ListeningSocket&) = delete;
	ListeningSocket(ListeningSocket&&) = delete;
	ListeningSocket& operator= (const ListeningSocket&) = delete;
	ListeningSocket& operator= (ListeningSocket&&) = delete;

	void Process(const std::string & pMessage);

	void CloseConnection(bool pFullClose = true);
	void AddSendMessage(const std::string & pMessage);
};

