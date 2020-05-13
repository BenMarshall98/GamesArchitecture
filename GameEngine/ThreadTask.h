#pragma once
#include <thread>

class ThreadTask
{
	std::thread mThread;
	bool mRunning = false;
	bool mClose = false;

public:
	ThreadTask();
	~ThreadTask();

	ThreadTask(const ThreadTask&) = delete;
	ThreadTask(ThreadTask&&) = delete;
	ThreadTask& operator= (const ThreadTask&) = delete;
	ThreadTask& operator= (ThreadTask&&) = delete;

	void Run(const std::function<void(ThreadTask *)> & pFunction);

	void Close();

	bool GetClose() const
	{
		return mClose;
	}
};

