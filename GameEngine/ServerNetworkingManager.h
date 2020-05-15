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
	ThreadTask mConnection;
	std::mutex mListeningMutex;
	
	std::vector<std::shared_ptr<ListeningSocket>> mListeningSockets;
	
	std::function<bool(const std::string &, ListeningSocket *)> mRecieveMessageFunction;

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

	void SetRecieveMessageFunction(const std::function<bool(const std::string &, ListeningSocket *)> & pRecieveMessageFunction)
	{
		mRecieveMessageFunction = pRecieveMessageFunction;
	}

	int NumberOfConnections()
	{
		std::lock_guard<std::mutex> lock(mListeningMutex);

		return mListeningSockets.size();
	}

	void AddSendMessage(const std::string & pMessage, int pId);
};

