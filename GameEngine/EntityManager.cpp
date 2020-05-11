#include "EntityManager.h"

#include "SystemManager.h"

EntityManager * EntityManager::mInstance = nullptr;

void EntityManager::AddEntity(const std::shared_ptr<Entity> & pEntity)
{
	mEntities.push_back(pEntity);

	SystemManager::Instance()->AddEntity(pEntity);
}

void EntityManager::UpdateEntity(Entity* pEntity)
{
	for (auto& entity : mEntities)
	{
		if (entity.get() == pEntity)
		{
			SystemManager::Instance()->UpdateEntity(entity);
			break;
		}
	}
}

void EntityManager::RemoveEntity(Entity* pEntity)
{
	for (auto i = 0u; i < mEntities.size(); i++)
	{
		if (mEntities[i].get() == pEntity)
		{
			SystemManager::Instance()->RemoveEntity(mEntities[i]);
			mEntities.erase(mEntities.begin() + i);
			break;
		}
	}
}

void EntityManager::Update(const float pDeltaTime)
{
	SystemManager::Instance()->Update(pDeltaTime);

	for (auto & entity : mEntities)
	{
		entity->Update(pDeltaTime);
	}
}

void EntityManager::Render()
{
	SystemManager::Instance()->Render();

	for (auto & entity : mEntities)
	{
		entity->Render();
	}
}

void EntityManager::Swap()
{
	for (auto & entity : mEntities)
	{
		entity->Swap();
	}
}

void EntityManager::Reset()
{
	SystemManager::Instance()->Reset();

	mEntities.clear();
	mEntities.shrink_to_fit();
}

void EntityManager::MessageAll(Entity* pEntity, const std::string& pMessage)
{
	for (auto & entity : mEntities)
	{
		entity->Message(pEntity, pMessage);
	}
}
