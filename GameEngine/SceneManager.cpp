#include "SceneManager.h"


#include "EntityManager.h"
#include "SystemManager.h"
#include "ThreadTask.h"
#include "Win32Window.h"

SceneManager * SceneManager::mInstance = nullptr;

void SceneManager::Run(const std::shared_ptr<Scene>& pScene)
{
	mScenes.push(pScene);
	mScenes.top()->Load();

	LARGE_INTEGER timer;
	QueryPerformanceFrequency(&timer);

	const auto freq = timer.QuadPart;

	QueryPerformanceCounter(&timer);
	auto start = timer.QuadPart;

	const auto updateFunction = [this](ThreadTask * pThread)
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mMutex);
			mCv.wait(lock, [this] {return mUpdateReady; });

			if (mEnd)
			{
				lock.unlock();
				return;
			}

			mScenes.top()->Update(mDeltaTime);

			mUpdateProcessed = true;
			mUpdateReady = false;
			lock.unlock();
			mCv.notify_one();
		}
	};

	ThreadTask task;
	task.Run(updateFunction);

	while (Win32Window::WindowEvents())
	{
		if (mNextScene)
		{
			mScenes.push(mNextScene);
			mScenes.top()->Load();

			mNextScene = nullptr;
		}

		if (mCloseScene)
		{
			mScenes.top()->Unload();
			mScenes.pop();

			if (mScenes.empty())
			{
				break;
			}

			mCloseScene = false;
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

		mDeltaTime = static_cast<double>(stop - start) / freq;

		start = stop;

		{
			std::lock_guard<std::mutex> lock(mMutex);
			mUpdateReady = true;
			mUpdateProcessed = false;
		}

		mCv.notify_one();
		
		mScenes.top()->Render();

		{
			std::unique_lock<std::mutex> lock(mMutex);
			mCv.wait(lock, [this] {return mUpdateProcessed; });
		}

		mScenes.top()->Swap();
	}

	std::unique_lock<std::mutex> lock(mMutex);

	mCv.wait(lock, [this] {return mUpdateProcessed; });
	
	mUpdateReady = true;
	mEnd = true;

	lock.unlock();
	mCv.notify_one();

	task.Close();

	while(!mScenes.empty())
	{
		mScenes.top()->Unload();
		mScenes.pop();
	}
}