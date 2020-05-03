#include "IpAddress.h"

#include <WS2tcpip.h>

IpAddress::IpAddress(const int pPort, const std::string& pAddress) : mPeer()
{
	mPeer.sin_family = AF_INET;
	mPeer.sin_port = htons(pPort);

	if (pAddress.empty())
	{
		mPeer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	}
	else
	{
		inet_pton(mPeer.sin_family, pAddress.c_str(), &mPeer.sin_addr);
	}
}
