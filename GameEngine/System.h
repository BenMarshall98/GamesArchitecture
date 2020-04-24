#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Entity.h"

class System
{
	std::vector<ComponentType> mComponentTypes;
	std::vector<std::shared_ptr<Entity>> mNewEntities;
	std::vector<std::shared_ptr<Entity>> mRemoveEntities;
	
protected:
	std::vector<std::shared_ptr<Entity>> mEntities;

public:
	explicit System(const std::vector<ComponentType> & pComponentTypes);
	virtual ~System() = default;

	System(const System &) = delete;
	System(System&&) = delete;
	System & operator= (const System &) = delete;
	System & operator= (System&&) = delete;

	virtual void Action(float pDeltaTime);
	
	void AddEntity(const std::shared_ptr<Entity> & pEntity);
	void UpdateEntity(const std::shared_ptr<Entity> & pEntity);
	void RemoveEntity(const std::shared_ptr<Entity> & pEntity);
	void Reset();
};

