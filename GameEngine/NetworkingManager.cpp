#include "NetworkingManager.h"

void NetworkingManager::AddRecieveMessage(const std::string& pMessage)
{
	//TODO: See if there is a faster way
	std::unique_lock<std::mutex> lock(mMutex);
	
	mRecieveMessages.push_back(pMessage);
}

std::vector<std::string> NetworkingManager::GetRecievedMessages()
{
	std::unique_lock<std::mutex> lock(mMutex);

	const auto result = mRecieveMessages;
	mRecieveMessages.shrink_to_fit();
	mRecieveMessages.clear();

	return result;
}

void NetworkingManager::AddSendMessage(const std::string& pMessage)
{
	mSendMessages.push_back(pMessage);
}