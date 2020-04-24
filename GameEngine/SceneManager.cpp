#include "SceneManager.h"


#include "EntityManager.h"
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

			mCloseScene = false;
		}
		
		QueryPerformanceCounter(&timer);
		const auto stop = timer.QuadPart;

		const auto deltaTime = static_cast<double>(stop - start) / freq;

		start = stop;
		
		mScenes.top()->Update(deltaTime);
		mScenes.top()->Render();

		EntityManager::Instance()->Swap();
	}
}
