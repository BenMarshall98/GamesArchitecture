#include "SceneManager.h"

#include "Win32Window.h"

SceneManager * SceneManager::mInstance = nullptr;

void SceneManager::Run(const std::shared_ptr<Scene>& pScene)
{
	mScenes.push(pScene);
	mScenes.top()->Load();

	while (Win32Window::windowEvents())
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

		//TODO: Calculate Delta Time
		mScenes.top()->Update(0.016f);
		mScenes.top()->Render();
	}
}
