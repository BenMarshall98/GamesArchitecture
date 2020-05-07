#pragma once



#include <thread>

#include "IpAddress.h"
#include "NetworkingManager.h"

class ClientNetworkingManager final : public NetworkingManager
{
	std::mutex mSendMutex;
	std::condition_variable mSendConditionVariable;
	std::vector<std::string> mSendMessages;
	
	std::thread mRecieveConnection;
	std::thread mSendConnection;
	
	bool mClose = false;
	ClientNetworkingManager();
	static ClientNetworkingManager * mInstance;

public:
	static ClientNetworkingManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new ClientNetworkingManager();
		}

		return mInstance;
	}
	
	~ClientNetworkingManager();

	ClientNetworkingManager(const ClientNetworkingManager&) = delete;
	ClientNetworkingManager(ClientNetworkingManager&&) = delete;
	ClientNetworkingManager& operator= (const ClientNetworkingManager&) = delete;
	ClientNetworkingManager& operator= (ClientNetworkingManager&&) = delete;

	bool StartListening(const IpAddress & pAddress) override;
	void Send();
	void Process(const std::string & pMessage);
	void Recieve();

	void CloseConnection(bool pFullClose = true);
	void AddSendMessage(const std::string& pMessage) override;
};
