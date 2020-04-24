#pragma once
#include "System.h"

class SystemManager
{
	std::vector<std::unique_ptr<System>> mRenderSystems;
	std::vector<std::unique_ptr<System>> mUpdateSystems;

	static SystemManager * mInstance;
	SystemManager() = default;

public:
	~SystemManager() = default;

	static SystemManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new SystemManager();
		}

		return mInstance;
	}

	SystemManager(const SystemManager &) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager & operator= (const SystemManager &) = delete;
	SystemManager & operator= (SystemManager&&) = delete;

	void AddUpdateSystem(std::unique_ptr<System> pUpdateSystem);
	void AddRenderSystem(std::unique_ptr<System> pRenderSystem);

	void Update(float pDeltaTime);
	void Render();

	void AddEntity(const std::shared_ptr<Entity> & pEntity);
	void UpdateEntity(const std::shared_ptr<Entity> & pEntity);
	void RemoveEntity(const std::shared_ptr<Entity> & pEntity);
	void Reset();
};