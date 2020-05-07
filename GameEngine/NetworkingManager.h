#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <mutex>
#include <vector>
#include <WinSock2.h>
#include "IpAddress.h"

class NetworkingManager
{
	std::mutex mRecieveMutex;
	std::vector<std::string> mRecieveMessages;
	
protected:
	SOCKET mSocket;
	NetworkingManager() = default;

public:
	virtual ~NetworkingManager() = default;

	NetworkingManager(const NetworkingManager&) = delete;
	NetworkingManager(NetworkingManager&&) = delete;
	NetworkingManager& operator= (const NetworkingManager&) = delete;
	NetworkingManager& operator= (NetworkingManager&) = delete;

	virtual bool StartListening(const IpAddress& pAddress) = 0;

	void AddRecieveMessage(const std::string & pMessage);
	std::vector<std::string> GetRecievedMessages();

	virtual void AddSendMessage(const std::string & pMessage) = 0;
};

