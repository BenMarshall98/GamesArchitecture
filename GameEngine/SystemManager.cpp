#include "SystemManager.h"

SystemManager * SystemManager::mInstance = nullptr;

void SystemManager::AddUpdateSystem(const std::shared_ptr<System> & pUpdateSystem)
{
	mUpdateSystems.emplace_back(pUpdateSystem);
}

void SystemManager::AddRenderSystem(const std::shared_ptr<System> & pRenderSystem)
{
	mRenderSystems.emplace_back(pRenderSystem);
}

void SystemManager::Update(const float pDeltaTime)
{
	for (auto & updateSystem : mUpdateSystems)
	{
		updateSystem->Action(pDeltaTime);
	}
}

void SystemManager::Render()
{
	for (auto & renderSystem : mRenderSystems)
	{
		renderSystem->Action(0.0f);
	}
}

void SystemManager::AddEntity(const std::shared_ptr<Entity>& pEntity)
{
	for (auto & updateSystem : mUpdateSystems)
	{
		updateSystem->AddEntity(pEntity);
	}

	for (auto & renderSystem : mRenderSystems)
	{
		renderSystem->AddEntity(pEntity);
	}
}

void SystemManager::UpdateEntity(const std::shared_ptr<Entity>& pEntity)
{
	for (auto & updateSystem : mUpdateSystems)
	{
		updateSystem->UpdateEntity(pEntity);
	}

	for (auto & renderSystem : mRenderSystems)
	{
		renderSystem->UpdateEntity(pEntity);
	}
}

void SystemManager::RemoveEntity(const std::shared_ptr<Entity>& pEntity)
{
	for (auto & updateSystem : mUpdateSystems)
	{
		updateSystem->RemoveEntity(pEntity);
	}

	for (auto & renderSystem : mRenderSystems)
	{
		renderSystem->RemoveEntity(pEntity);
	}
}

void SystemManager::Reset()
{
	for (auto & updateSystem : mUpdateSystems)
	{
		updateSystem->Reset();
	}

	for (auto & renderSystem : mRenderSystems)
	{
		renderSystem->Reset();
	}
}
