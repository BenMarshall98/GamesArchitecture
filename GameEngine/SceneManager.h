#pragma once
#include <memory>
#include <stack>

#include "Scene.h"

class SceneManager
{
	std::stack<std::shared_ptr<Scene>> mScenes;
	std::shared_ptr<Scene> mNextScene;

	bool mCloseScene = false;
	
	static SceneManager * mInstance;

	SceneManager() = default;
	
public:
	static SceneManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new SceneManager();
		}

		return mInstance;
	}

	~SceneManager() = default;

	SceneManager(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator= (const SceneManager&) = delete;
	SceneManager& operator= (SceneManager&&) = delete;

	void Run(const std::shared_ptr<Scene> & pScene);

	void NextScene(const std::shared_ptr<Scene> & pScene)
	{
		mNextScene = pScene;
	}
	
	void CloseScene()
	{
		mCloseScene = true;
	}

	std::shared_ptr<Scene> GetCurrentScene() const
	{
		return mScenes.top();
	}
};

