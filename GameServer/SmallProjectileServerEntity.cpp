#include "SmallProjectileServerEntity.h"

#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/SphereObject.h"

SmallProjectileServerEntity::SmallProjectileServerEntity(const glm::vec3& pPosition, const glm::vec3& pVelocity)
{
	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.01f));

	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, pVelocity, 0.01f, 0.01f);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void SmallProjectileServerEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void SmallProjectileServerEntity::Render()
{
	//Do Nothing
}
