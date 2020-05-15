#pragma once



#include <thread>

#include "IpAddress.h"
#include "NetworkingManager.h"
#include "ThreadTask.h"

class ClientNetworkingManager final : public NetworkingManager
{
	ThreadTask mRecieveConnection;
	ThreadTask mSendConnection;
	
	std::vector<std::string> mSendMessages;
	std::mutex mSendMutex;
	std::condition_variable mSendConditionVariable;

	std::function<bool(const std::string &)> mRecieveMessageFunction;
	
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
	void Process(const std::string & pMessage);

	void CloseConnection(bool pFullClose = true);
	void AddSendMessage(const std::string& pMessage) override;

	void SetRecieveMessageFunction(const std::function<bool(const std::string &)> & pRecieveMessageFunction)
	{
		mRecieveMessageFunction = pRecieveMessageFunction;
	}
};
