#include "PlaneEntity.h"

#include "PhysicsComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "PlaneObject.h"

PlaneEntity::PlaneEntity()
{
	const auto renderComponent = std::make_shared<RenderComponent>(
		ResourceManager::Instance()->LoadShader("PlaneVertexShader", "PlaneFragmentShader"),
		ResourceManager::Instance()->LoadModel("Assets/Models/plane.obj"), nullptr);

	const auto positionComponent = std::make_shared<PositionComponent>(glm::vec3(0.0f), glm::vec3(10.0f));

	const auto planeObject = std::make_shared<PlaneObject>(this, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	const auto physicsComponent = std::make_shared<PhysicsComponent>(planeObject, true);

	AddComponent(renderComponent, false);
	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void PlaneEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void PlaneEntity::Render()
{
	//Do Nothing
}