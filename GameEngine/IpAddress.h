#pragma once

#pragma comment(lib, "ws2_32.lib")

#include <string>
#include <WinSock2.h>

class IpAddress
{
	sockaddr_in mPeer;

public:
	explicit IpAddress(int pPort, const std::string & pAddress = "");
	~IpAddress() = default;

	IpAddress(const IpAddress&) = delete;
	IpAddress(IpAddress&&) = delete;
	IpAddress& operator= (const IpAddress&) = delete;
	IpAddress& operator= (IpAddress&&) = delete;

	sockaddr_in GetPeer() const
	{
		return mPeer;
	}
};
