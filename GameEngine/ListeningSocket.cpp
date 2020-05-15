#include "ListeningSocket.h"


#include <iomanip>
#include <iostream>
#include <sstream>

#include "ServerNetworkingManager.h"

int ListeningSocket::ID = 0;

ListeningSocket::ListeningSocket(const SOCKET & pSocket, const std::function<bool(const std::string &, ListeningSocket *)> & pRecieveMessageFunction) : mSocket(pSocket), mID(ID), mRecieveMessageFunction(pRecieveMessageFunction)
{
	std::cout << "Connection Started With ID " << mID << std::endl;

	const auto recieveFunction = [this](ThreadTask * pThread)
	{
		while (true)
		{
			char buffer[11] = "";
			if (recv(mSocket, buffer, 10, 0) == SOCKET_ERROR)
			{
				if (pThread->GetClose())
				{
					return;
				}

				std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;

				CloseConnection(false);

				break;
			}

			std::string message = buffer;

			std::istringstream str(message.substr(0, 4));

			int size;
			str >> size;

			str = std::istringstream(message.substr(4, 4));

			int checksum;
			str >> checksum;

			message = message.erase(0, 8);

			size -= 8;

			if (size > 20)
			{
				int i = 0;
			}

			while (message.size() != size)
			{
				char tempBuffer[11] = "";
				int left = size - message.size();
				left = left > 10 ? 10 : left;

				if (recv(mSocket, tempBuffer, left, 0) == SOCKET_ERROR)
				{
					if (pThread->GetClose())
					{
						break;
					}

					std::cerr << "Receive failed with " << WSAGetLastError() << std::endl;

					CloseConnection(false);

					return;
				}

				message += tempBuffer;
			}

			auto checking = 0u;

			for (int i = 0; i < message.size(); i++)
			{
				checking += static_cast<int>(message[i]);
			}

			if (checksum != checking % 10000)
			{
				std::cerr << "Checksum failed " << std::endl;
				break;
			}

			std::cout << "Connection " << mID << " Received Message " << message << std::endl;

			if (message == "q")
			{
				CloseConnection(false);
			}

			if (!mRecieveMessageFunction(message, this))
			{
				ServerNetworkingManager::Instance()->AddRecieveMessage("C" + std::to_string(mID) + message);
			}
		}
	};

	const auto sendFunction = [this](ThreadTask * pThread)
	{
		LARGE_INTEGER timer;
		QueryPerformanceFrequency(&timer);

		const auto freq = timer.QuadPart;

		QueryPerformanceCounter(&timer);
		auto start = timer.QuadPart;
		
		while (true)
		{
			std::unique_lock<std::mutex> lock(mSendMutex);
			//mSendConditionVariable.wait(lock, [this] {return !mSendMessages.empty(); });

			const auto message = mSendMessages;
			mSendMessages.clear();

			lock.unlock();

			for (int i = 0; i < message.size(); i++)
			{
				Process(message[i]);
			}

			QueryPerformanceCounter(&timer);
			auto stop = timer.QuadPart;

			auto timeElapsed = static_cast<double>(stop - start) / freq;
			auto difference = mTargetTime - timeElapsed;

			if (difference > 0.005f)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(difference * 1000000.0f)));
				QueryPerformanceCounter(&timer);
				stop = timer.QuadPart;
			}
			else if (difference > 0.0f)
			{
				while (difference > 0.0f)
				{
					QueryPerformanceCounter(&timer);
					stop = timer.QuadPart;
					timeElapsed = static_cast<double>(stop - start) / freq;
					difference = mTargetTime - timeElapsed;
				}
			}

			const auto deltaTime = static_cast<float>(static_cast<double>(stop - start) / freq);

			start = stop;

			std::ostringstream str;

			str << "NetA";

			const auto time = 1.0f / deltaTime;
			
			uint32_t num = *((uint32_t*)&time);
			str << std::setw(8) << std::setfill('0') << std::hex << num;
			
			const auto timeMessage = str.str();

			if (pThread->GetClose())
			{
				return;
			}
			
			AddSendMessage(timeMessage);

			
		}
	};

	mRecieveConnection.Run(recieveFunction);
	mSendConnection.Run(sendFunction);
	ID++;
}

ListeningSocket::~ListeningSocket()
{
	mRecieveConnection.Close();
	mSendConnection.Close();
}

void ListeningSocket::Process(const std::string& pMessage)
{
	const auto size = pMessage.size() + 8u;

	std::ostringstream str;

	str << std::setfill('0') << std::setw(4) << size;

	auto checksum = 0u;

	for (int i = 0; i < pMessage.size(); i++)
	{
		checksum += static_cast<int>(pMessage[i]);
	}

	str << std::setfill('0') << std::setw(4) << checksum % 10000;

	str << pMessage;

	auto message = str.str();

	if (send(mSocket, message.c_str(), size, 0) == SOCKET_ERROR)
	{
		if (mSendConnection.GetClose())
		{
			return;
		}

		std::cerr << "Send failed with " << WSAGetLastError() << std::endl;

		CloseConnection(false);
	}

	std::cout << "Connection " << mID << " Send Message " << pMessage << std::endl;
}

void ListeningSocket::AddSendMessage(const std::string& pMessage)
{
	std::lock_guard<std::mutex> lock(mSendMutex);

	mSendMessages.push_back(pMessage);

	mSendConditionVariable.notify_one();
}

void ListeningSocket::CloseConnection(const bool pFullClose)
{
	mSendConnection.Close();
	mRecieveConnection.Close();
	
	if (pFullClose)
	{
		Process("q");
	}

	std::cout << "Connection Ended With ID " << mID << std::endl;

	closesocket(mSocket);

	ServerNetworkingManager::Instance()->RemoveConnection(this);
}