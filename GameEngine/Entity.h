#pragma once

#include <memory>
#include <vector>

#include "Component.h"

class Entity
{
protected:
	std::shared_ptr<Component> mComponents [static_cast<int>(ComponentType::NONE)];

public:
	Entity() = default;
	~Entity() = default;

	Entity(const Entity &) = delete;
	Entity(Entity&&) = delete;
	Entity & operator= (const Entity &) = delete;
	Entity & operator= (Entity&&) = delete;

	void AddComponent(std::shared_ptr<Component> pComponent);
	void RemoveComponent(std::shared_ptr<Component> pComponent);
	std::shared_ptr<Component> GetComponentByType(ComponentType pType);
	bool HasComponents(std::vector<ComponentType> pTypes);
};

