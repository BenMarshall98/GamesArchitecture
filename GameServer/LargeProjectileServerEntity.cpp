#include "LargeProjectileServerEntity.h"

#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/SphereObject.h"

LargeProjectileServerEntity::LargeProjectileServerEntity(const glm::vec3& pPosition, const glm::vec3& pVelocity)
{
	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.02f));

	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, pVelocity, 0.05f, 0.02f);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void LargeProjectileServerEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void LargeProjectileServerEntity::Render()
{
	//Do Nothing
}

void LargeProjectileServerEntity::Message(Entity* pEntity, const std::string& pMessage)
{
	if (pMessage == "Explode")
	{
		const auto positionComponent1 = std::dynamic_pointer_cast<PositionComponent>(GetComponentByType(ComponentType::POSITION));
		const auto positionComponent2 = std::dynamic_pointer_cast<PositionComponent>(pEntity->GetComponentByType(ComponentType::POSITION));

		const auto position1 = positionComponent1->GetUpdatePosition();
		const auto position2 = positionComponent2->GetUpdatePosition();

		const auto physicsComponent = std::dynamic_pointer_cast<PhysicsComponent>(GetComponentByType(ComponentType::PHYSICS));
		const auto collisionObject = physicsComponent->GetCollisionObject();
		auto distance = length(position1 - position2);
		distance = 1.0f - glm::smoothstep(0.0f, 0.5f, distance);

		const auto velocity = (position2 - position1) * distance * 20.0f;

		collisionObject->ApplyImpluse(velocity);
	}
}
