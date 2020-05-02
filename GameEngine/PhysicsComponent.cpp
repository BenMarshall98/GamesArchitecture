#include "PhysicsComponent.h"

#include "PhysicsManager.h"

PhysicsComponent::PhysicsComponent(const std::shared_ptr<CollisionObject>& pCollisionObject, const bool pInvincible) :
	Component(ComponentType::PHYSICS), mCollisionObject(pCollisionObject), mInvincible(pInvincible)
{
	if (mInvincible)
	{
		PhysicsManager::Instance()->AddInfiniteCollisionObject(mCollisionObject);
	}
	else
	{
		if (mCollisionObject->GetType() == RigidBodyType::DYNAMIC)
		{
			PhysicsManager::Instance()->AddDynamicCollisionObject(mCollisionObject);
		}
		else
		{
			PhysicsManager::Instance()->AddStaticCollisionObject(mCollisionObject);
		}
	}
}

PhysicsComponent::~PhysicsComponent()
{
	if (mInvincible)
	{
		PhysicsManager::Instance()->RemoveInfiniteCollisionObject(mCollisionObject);
	}
	else
	{
		if (mCollisionObject->GetType() == RigidBodyType::DYNAMIC)
		{
			PhysicsManager::Instance()->RemoveDynamicCollisionObject(mCollisionObject);
		}
		else
		{
			PhysicsManager::Instance()->RemoveStaticCollisionObject(mCollisionObject);
		}
	}
}

void PhysicsComponent::Swap()
{
	//Do Nothing
}