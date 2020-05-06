#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class Entity
{
	static uint32_t mStaticId;
	uint32_t mId;
	
protected:
	std::shared_ptr<Component> mComponents [static_cast<int>(ComponentType::NONE)];

public:
	Entity();
	virtual ~Entity() = default;

	Entity(const Entity &) = delete;
	Entity(Entity&&) = delete;
	Entity & operator= (const Entity &) = delete;
	Entity & operator= (Entity&&) = delete;

	void AddComponent(const std::shared_ptr<Component> & pComponent, bool pUpdate = true);
	void RemoveComponent(const std::shared_ptr<Component> & pComponent, bool pUpdate = true);
	std::shared_ptr<Component> GetComponentByType(ComponentType pType);
	bool HasComponents(const std::vector<ComponentType> & pTypes) const;
	
	virtual void Update(float pDeltaTime) = 0;
	virtual void Render() = 0;
	virtual void Swap();

	uint32_t GetId() const
	{
		return mId;
	}

	//TODO: Call
	static void Reset()
	{
		mStaticId = 0;
	}
};

