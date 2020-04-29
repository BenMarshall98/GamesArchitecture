#pragma once

#include <functional>
#include <vector>

#include <WinSock2.h>
#include "IpAddress.h"
#include "ListeningSocket.h"

class NetworkingManager
{
	std::vector<std::shared_ptr<ListeningSocket>> mListeningSockets;
	SOCKET mSocket;
	bool mClose = false;
	
	NetworkingManager();
	static NetworkingManager * mInstance;

public:
	static NetworkingManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new NetworkingManager();
		}

		return mInstance;
	}

	~NetworkingManager();

	bool StartListening(const IpAddress & pAddress);
	void RemoveConnection(ListeningSocket * pListeningSocket);
	void CloseServer();
};

