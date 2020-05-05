#pragma once



#include <thread>

#include "IpAddress.h"

class ClientNetworkingManager
{
	static int ID;
	int mID;
	SOCKET mSocket;
	std::thread mConnection;
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

	bool StartListening(const IpAddress & pAddress);
	void Send(const std::string & pMessage);
	void Recieve();

	void CloseConnection(bool pFullClose = true);
};