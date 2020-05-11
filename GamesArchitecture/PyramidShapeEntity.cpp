#include "PyramidShapeEntity.h"

#include "PhysicsComponent.h"
#include "PlaybackComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SphereObject.h"

PyramidShapeEntity::PyramidShapeEntity(const glm::vec3& pPosition, bool pBase)
{
	const auto renderComponent = std::make_shared<RenderComponent>(
		ResourceManager::Instance()->LoadShader("SimpleVertexProgram", "SimpleFragmentProgram"),
		ResourceManager::Instance()->LoadModel("Assets/Models/sphere.obj"), nullptr);

	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.01f));

	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, glm::vec3(0.0f), (pBase ? 0.01f : 0.00f), 0.01f);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	if (pBase)
	{
		const auto playbackComponent = std::make_shared<PlaybackComponent>();
		
		AddComponent(playbackComponent, false);
	}

	AddComponent(renderComponent, false);
	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void PyramidShapeEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void PyramidShapeEntity::Render()
{
	//Do Nothing
}