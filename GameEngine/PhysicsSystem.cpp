#include "PhysicsSystem.h"

#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "PhysicsManager.h"

PhysicsSystem::PhysicsSystem() : System( {ComponentType::PHYSICS, ComponentType::POSITION})
{
}

void PhysicsSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	if (mSimulation)
	{
		PhysicsManager::Instance()->Update(pDeltaTime);

		for (auto & entity : mEntities)
		{
			const auto positionComponent = std::dynamic_pointer_cast<PositionComponent>(entity->GetComponentByType(ComponentType::POSITION));
			const auto physicsComponent = std::dynamic_pointer_cast<PhysicsComponent>(entity->GetComponentByType(ComponentType::PHYSICS));

			const auto collisionObject = physicsComponent->GetCollisionObject();

			positionComponent->SetUpdatePosition(collisionObject->GetCurrentPosition());
		}
	}
}