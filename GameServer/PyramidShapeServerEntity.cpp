#include "PyramidShapeServerEntity.h"

#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/SphereObject.h"

PyramidShapeServerEntity::PyramidShapeServerEntity(const glm::vec3& pPosition, bool pBase)
{
	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.01f));

	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, glm::vec3(0.0f), (pBase ? 0.01f : 0.00f), 0.01f);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void PyramidShapeServerEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void PyramidShapeServerEntity::Render()
{
	//Do Nothing
}
