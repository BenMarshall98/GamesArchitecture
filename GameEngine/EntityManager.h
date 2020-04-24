#pragma once
#include <memory>
#include <vector>

#include "Entity.h"

class EntityManager
{
	std::vector<std::shared_ptr<Entity>> mEntities;
	
	static EntityManager * mInstance;
	EntityManager() = default;

public:
	~EntityManager() = default;
	
	static EntityManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new EntityManager();
		}

		return mInstance;
	}

	EntityManager(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager & operator= (const EntityManager&) = delete;
	EntityManager & operator= (EntityManager&&) = delete;

	void AddEntity(const std::shared_ptr<Entity> & pEntity);
	void UpdateEntity(Entity * pEntity);
	void RemoveEntity(Entity * pEntity);

	void Update(float pDeltaTime);
	void Render();
	void Swap();
};
