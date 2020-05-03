#include "SystemManager.h"

SystemManager * SystemManager::mInstance = nullptr;

void SystemManager::AddUpdateSystem(std::unique_ptr<System> pUpdateSystem)
{
	mUpdateSystems.emplace_back(std::move(pUpdateSystem));
}

void SystemManager::AddRenderSystem(std::unique_ptr<System> pRenderSystem)
{
	mRenderSystems.emplace_back(std::move(pRenderSystem));
}

void SystemManager::AddNetworkSystem(std::unique_ptr<System> pNetworkSystem)
{
	mNetworkSystems.emplace_back(std::move(pNetworkSystem));
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

void SystemManager::Network()
{
	for (auto & networkSystem : mNetworkSystems)
	{
		networkSystem->Action(0.0f);
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
