#include "Entity.h"

#include "EntityManager.h"

void Entity::AddComponent(const std::shared_ptr<Component> & pComponent, const bool pUpdate)
{
	mComponents[static_cast<int>(pComponent->GetType())] = pComponent;

	if (pUpdate)
	{
		EntityManager::Instance()->UpdateEntity(this);
	}
}

void Entity::RemoveComponent(const std::shared_ptr<Component> & pComponent, const bool pUpdate)
{
	mComponents[static_cast<int>(pComponent->GetType())] = nullptr;

	if (pUpdate)
	{
		EntityManager::Instance()->UpdateEntity(this);
	}
}

std::shared_ptr<Component> Entity::GetComponentByType(ComponentType pType)
{
	return mComponents[static_cast<int>(pType)];
}

bool Entity::HasComponents(const std::vector<ComponentType> & pTypes) const
{
	auto hasComponents = true;

	for (auto & type : pTypes)
	{
		if (!mComponents[static_cast<int>(type)])
		{
			hasComponents = false;
		}
	}

	return false;
}
