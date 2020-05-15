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
	
	ThreadTask mRecieveConnection;
	ThreadTask mSendConnection;

	std::mutex mSendMutex;
	std::vector<std::string> mSendMessages;
	std::condition_variable mSendConditionVariable;
	std::function<bool(const std::string &, ListeningSocket *)> mRecieveMessageFunction;

	float mTargetTime = 0.016f;
	int mID;
	SOCKET mSocket;

public:
	explicit ListeningSocket(const SOCKET & pSocket, const std::function<bool(const std::string &, ListeningSocket *)> & pRecieveMessageFunction);
	~ListeningSocket();

	ListeningSocket(const ListeningSocket&) = delete;
	ListeningSocket(ListeningSocket&&) = delete;
	ListeningSocket& operator= (const ListeningSocket&) = delete;
	ListeningSocket& operator= (ListeningSocket&&) = delete;

	void Process(const std::string & pMessage);

	void CloseConnection(bool pFullClose = true);
	void AddSendMessage(const std::string & pMessage);

	void SetTargetTime(const float pTargetTime)
	{
		mTargetTime = pTargetTime;
	}
};

