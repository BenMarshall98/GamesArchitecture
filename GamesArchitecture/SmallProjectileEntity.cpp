#include "SmallProjectileEntity.h"

#include "PhysicsComponent.h"
#include "PlaybackComponent.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "SphereObject.h"

SmallProjectileEntity::SmallProjectileEntity(const glm::vec3& pPosition, const glm::vec3& pVelocity)
{
	const auto renderComponent = std::make_shared<RenderComponent>(
		ResourceManager::Instance()->LoadShader("SimpleVertexProgram", "SimpleFragmentProgram"),
		ResourceManager::Instance()->LoadModel("Assets/Models/sphere.obj"), nullptr);

	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.01f));

	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, pVelocity, 0.01f, 0.01f);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	const auto playbackComponent = std::make_shared<PlaybackComponent>();

	AddComponent(renderComponent, false);
	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
	AddComponent(playbackComponent, false);
}

void SmallProjectileEntity::Update(float pDeltaTime)
{
	//Do Nothing
}

void SmallProjectileEntity::Render()
{
	//Do Nothing
}
