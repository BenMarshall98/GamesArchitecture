#include "GrenageProjectileServerEntity.h"



#include "../GameEngine/EntityManager.h"
#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/SphereObject.h"

GrenageProjectileServerEntity::GrenageProjectileServerEntity(const glm::vec3& pPosition, const glm::vec3& pVelocity)
{
	const auto positionComponent = std::make_shared<PositionComponent>(pPosition, glm::vec3(0.01f));

	const auto function = [this](CollisionObject *, CollisionObject *)
	{
		if (mFirst)
		{
			mExplode = true;
			mFirst = false;
		}
	};
	
	const auto sphereObject = std::make_shared<SphereObject>(this, pPosition, pVelocity, 0.01f, 0.01f, function);

	const auto physicsComponent = std::make_shared<PhysicsComponent>(sphereObject);

	AddComponent(positionComponent, false);
	AddComponent(physicsComponent, false);
}

void GrenageProjectileServerEntity::Update(float pDeltaTime)
{
	if (mExplode)
	{
		EntityManager::Instance()->MessageAll(this, "Explode");
		mExplode = false;
	}
}

void GrenageProjectileServerEntity::Render()
{
	//Do Nothing
}

void GrenageProjectileServerEntity::Message(Entity* pEntity, const std::string& pMessage)
{
	if (pEntity == this)
	{
		return;
	}

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

		const auto velocity = (position1 - position2) * distance * 20.0f;

		collisionObject->ApplyImpluse(velocity);
	}
}
