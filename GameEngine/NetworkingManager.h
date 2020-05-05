#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <mutex>
#include <vector>
#include <WinSock2.h>
#include "IpAddress.h"

class NetworkingManager
{
	std::mutex mMutex;
	
	std::vector<std::string> mRecieveMessages;
	std::vector<std::string> mTempRecieveMessages;
	std::vector<std::string> mSendMessages;
	
protected:
	SOCKET mSocket;
	
	NetworkingManager() = default;

public:
	~NetworkingManager() = default;

	NetworkingManager(const NetworkingManager&) = delete;
	NetworkingManager(NetworkingManager&&) = delete;
	NetworkingManager& operator= (const NetworkingManager&) = delete;
	NetworkingManager& operator= (NetworkingManager&) = delete;

	virtual bool StartListening(const IpAddress& pAddress) = 0;
	virtual void SendAllMessages() = 0;

	void AddRecieveMessage(const std::string & pMessage);
	std::vector<std::string> GetRecievedMessages();

	void AddSendMessage(const std::string & pMessage);
};

