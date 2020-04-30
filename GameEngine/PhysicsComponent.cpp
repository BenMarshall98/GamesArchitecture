#include "PhysicsComponent.h"

#include "PhysicsManager.h"

PhysicsComponent::PhysicsComponent(const std::shared_ptr<CollisionObject>& pCollisionObject) :
	Component(ComponentType::PHYSICS), mCollisionObject(pCollisionObject)
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

PhysicsComponent::~PhysicsComponent()
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

void PhysicsComponent::Swap()
{
	//Do Nothing
}