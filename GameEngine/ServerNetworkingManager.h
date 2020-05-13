#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <functional>
#include <vector>

#include <WinSock2.h>
#include "IpAddress.h"
#include "ListeningSocket.h"
#include "NetworkingManager.h"

class ServerNetworkingManager final : public NetworkingManager
{
	std::vector<std::shared_ptr<ListeningSocket>> mListeningSockets;

	std::mutex mListeningMutex;
	
	ThreadTask mConnection;

	ServerNetworkingManager();
	static ServerNetworkingManager * mInstance;

public:
	static ServerNetworkingManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new ServerNetworkingManager();
		}

		return mInstance;
	}

	~ServerNetworkingManager();

	ServerNetworkingManager(const ServerNetworkingManager&) = delete;
	ServerNetworkingManager(ServerNetworkingManager&&) = delete;
	ServerNetworkingManager& operator= (const ServerNetworkingManager&) = delete;
	ServerNetworkingManager& operator= (ServerNetworkingManager&&) = delete;

	bool StartListening(const IpAddress & pAddress) override;
	void RemoveConnection(ListeningSocket * pListeningSocket);
	void CloseServer();

	void AddSendMessage(const std::string& pMessage) override;
};

