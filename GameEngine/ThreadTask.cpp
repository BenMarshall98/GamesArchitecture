#include "ThreadTask.h"

#include "ThreadingManager.h"

ThreadTask::ThreadTask()
{
	ThreadingManager::Instance()->AddTask(this);
}

ThreadTask::~ThreadTask()
{
	ThreadingManager::Instance()->RemoveTask(this);
}

void ThreadTask::Run(const std::function<void(ThreadTask*)>& pFunction)
{
	mThread = std::thread(pFunction, this);
	mRunning = true;
}

void ThreadTask::Close()
{
	if (mRunning)
	{
		mThread.detach();
		mRunning = false;
	}
	
	mClose = true;
}
