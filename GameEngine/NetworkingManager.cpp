#include "NetworkingManager.h"

void NetworkingManager::AddRecieveMessage(const std::string& pMessage)
{
	//TODO: See if there is a faster way
	std::unique_lock<std::mutex> lock(mRecieveMutex);
	
	mRecieveMessages.push_back(pMessage);
}

std::vector<std::string> NetworkingManager::GetRecievedMessages()
{
	std::unique_lock<std::mutex> lock(mRecieveMutex);

	const auto result = mRecieveMessages;
	mRecieveMessages.shrink_to_fit();
	mRecieveMessages.clear();

	return result;
}