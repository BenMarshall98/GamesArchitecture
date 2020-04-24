#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(const std::shared_ptr<CollisionObject>& pCollisionObject) :
	Component(ComponentType::PHYSICS), mCollisionObject(pCollisionObject)
{
}

void PhysicsComponent::Swap()
{
	//Do Nothing
}