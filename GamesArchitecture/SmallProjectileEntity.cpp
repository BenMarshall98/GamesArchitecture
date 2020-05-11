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

void SmallProjectileEntity::Message(Entity* pEntity, const std::string& pMessage)
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
