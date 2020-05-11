#include "PlaneServerEntity.h"

#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PlaneObject.h"
#include "../GameEngine/PositionComponent.h"

PlaneServerEntity::PlaneServerEntity()
{
	const auto positionComponent = std::make_shared<PositionComponent>(glm::vec3(0.0f), glm::vec3(10.0f));

	const auto planeObject = std::make_shared<PlaneObject>(this, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	const auto physicsComponent = std::make_shared<PhysicsComponent>(planeObject, true);

	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void PlaneServerEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void PlaneServerEntity::Render()
{
	//Do Nothing
}

void PlaneServerEntity::Message(Entity* pEntity, const std::string& pMessage)
{
	//Do Nothing
}
