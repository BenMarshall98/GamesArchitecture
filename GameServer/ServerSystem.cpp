#include "ServerSystem.h"

#include <sstream>



#include "../GameEngine/EntityManager.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PlaybackComponent.h"
#include "../GameEngine/ServerNetworkingManager.h"
#include "GrenageProjectileServerEntity.h"
#include "LargeProjectileServerEntity.h"
#include "SmallProjectileServerEntity.h"

ServerSystem::ServerSystem(PyramidServerScene* pScene) :
	System({ComponentType::PHYSICS}), mScene(pScene)
{
}

void ServerSystem::Action(float pDeltaTime)
{
	//Get Networking Messages
	std::vector<std::string> messages = ServerNetworkingManager::Instance()->GetRecievedMessages();

	//Go Through Networking Messages
	for (int i = 0; i < messages.size(); i++)
	{
		auto offset = 0;
		
		const auto type = messages[i].substr(offset, 4);

		//TODO: Playback controls and other messages
		if (type == "AddP")
		{
			const auto projectileType = messages[i].substr(offset += 4, 1);

			offset += 1;

			glm::vec3 position;

			for (int j = 0; j < 3; j++)
			{
				const auto val = messages[i].substr(offset, 8);

				uint32_t num;
				std::istringstream str(val);
				str >> std::hex >> num;

				position[j] = *((float*)&num);

				offset += 8;
			}

			glm::vec3 velocity;

			for (int j = 0; j < 3; j++)
			{
				const auto val = messages[i].substr(offset, 8);

				uint32_t num;
				std::istringstream str(val);
				str >> std::hex >> num;

				velocity[j] = *((float*)&num);

				offset += 8;
			}

			if (projectileType == "S")
			{
				EntityManager::Instance()->AddEntity(std::make_shared<SmallProjectileServerEntity>(position, velocity));
			}
			else if (projectileType == "L")
			{
				EntityManager::Instance()->AddEntity(std::make_shared<LargeProjectileServerEntity>(position, velocity));
			}
			else if (projectileType == "G")
			{
				EntityManager::Instance()->AddEntity(std::make_shared<GrenageProjectileServerEntity>(position, velocity));
			}

			ServerNetworkingManager::Instance()->AddSendMessage(messages[i]);
		}
	}
	
	System::Action(pDeltaTime);

	if (mScene->GetSimulation())
	{
		const auto simulationTime = mScene->GetSimulationTime();

		std::ostringstream str;
		str << "Time";

		for (auto & entity : mEntities)
		{
			const auto physicsComponent = std::dynamic_pointer_cast<PhysicsComponent>(entity->GetComponentByType(ComponentType::PHYSICS));

			const auto collisionObject = physicsComponent->GetCollisionObject();

			if (collisionObject->GetType() == RigidBodyType::STATIC)
			{
				continue;
			}

			const auto currentPosition = collisionObject->GetCurrentPosition();
			const auto currentVelocity = collisionObject->GetCurrentVelocity();

			//TODO: Check epsilon

			const auto moving = glm::length(currentPosition - collisionObject->GetLastPosition()) > 0.001f;
			const auto id = entity->GetId();

			//TODO: Add to message
		}
	}
}