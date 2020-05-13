#pragma once

#include <vector>

#include "ThreadTask.h"

class ThreadingManager
{
	std::vector<ThreadTask *> mThreads;
	
	ThreadingManager() = default;
	static ThreadingManager * mInstance;

public:
	~ThreadingManager() = default;
	static ThreadingManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new ThreadingManager();
		}

		return mInstance;
	}

	ThreadingManager(const ThreadingManager&) = delete;
	ThreadingManager(ThreadingManager&&) = delete;
	ThreadingManager& operator= (const ThreadingManager&) = delete;
	ThreadingManager& operator= (ThreadingManager&&) = delete;

	ThreadTask * Task(const std::function<void(ThreadTask*)> & pFunction)
	{
		auto task = new ThreadTask();
		task->Run(pFunction);

		AddTask(task);

		return task;
	}

	void AddTask(ThreadTask * pTask)
	{
		mThreads.push_back(pTask);
	}

	void RemoveTask(ThreadTask * pTask)
	{
		for (int i = 0; i < mThreads.size(); i++)
		{
			if (mThreads[i] == pTask)
			{
				mThreads[i]->Close();
				mThreads.erase(mThreads.begin() + i);
				return;
			}
		}
	}

	void CloseAllThreads()
	{
		for (int i = 0; i < mThreads.size(); i++)
		{
			mThreads[i]->Close();
		}
	}
};

