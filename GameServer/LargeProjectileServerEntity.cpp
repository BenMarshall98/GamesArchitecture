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
