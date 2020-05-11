#include "ServerSystem.h"

#include <iomanip>
#include <sstream>

#include "../GameEngine/EntityManager.h"
#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/PlaybackComponent.h"
#include "../GameEngine/ServerNetworkingManager.h"
#include "GrenageProjectileServerEntity.h"
#include "LargeProjectileServerEntity.h"
#include "SmallProjectileServerEntity.h"

ServerSystem::ServerSystem(PyramidServerScene * pScene) :
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

		if (messages[i] == "ResetPyramid")
		{
			const auto size = mScene->SetReset();

			//TODO: Message
			continue;
		}
		if (messages[i] == "IncreasePyramid")
		{
			const auto size = mScene->IncreasePyramidSize();

			std::ostringstream str;
			str << "IPyr" << std::setw(2) << std::setfill('0') << size;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			continue;
		}
		if (messages[i] == "DecreasePyramid")
		{
			const auto size = mScene->DecreasePyramidSize();

			std::ostringstream str;
			str << "DPyr" << std::setw(2) << std::setfill('0') << size;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			continue;
		}
		if (messages[i] == "IncreasePlayback")
		{
			const auto size = mScene->IncreasePlaybackSpeed();

			std::ostringstream str;
			str << "IPla" << std::setw(2) << std::setfill('0') << size;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			continue;
		}
		if (messages[i] == "DecreasePlayback")
		{
			const auto size = mScene->DecreasePlaybackSpeed();

			std::ostringstream str;
			str << "DPla" << std::setw(2) << std::setfill('0') << size;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			continue;
		}
		if (messages[i] == "PausePlayback")
		{
			mScene->PausePlayback();

			ServerNetworkingManager::Instance()->AddSendMessage("PausePlayback");
			
			continue;
		}
		if (messages[i] == "UnpausePlayback")
		{
			mScene->UnpausePlayback();

			ServerNetworkingManager::Instance()->AddSendMessage("UnpausePlayback");

			continue;
		}
		if (messages[i] == "StepBackPlayback")
		{
			//TODO

			continue;
		}
		if (messages[i] == "StepUpPlayback")
		{
			//TODO

			continue;
		}
		
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

			if (!mScene->GetSimulation())
			{
				ServerNetworkingManager::Instance()->AddSendMessage("StartSimulation");
				mScene->StartSimulation();
			}
			
			ServerNetworkingManager::Instance()->AddSendMessage(messages[i]);
		}
	}
	
	System::Action(pDeltaTime);

	if (mScene->GetSimulationTime() > 4.0f && mScene->GetSimulation())
	{
		ServerNetworkingManager::Instance()->AddSendMessage("StartPlayback");
		mScene->StartPlayback();
	}

	if (mScene->GetSimulation())
	{
		const auto simulationTime = mScene->GetSimulationTime();

		std::ostringstream str;
		str << "Time";

		uint32_t num = *((uint32_t*)&simulationTime);
		str << std::setw(8) << std::setfill('0') << std::hex << num;

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

			const auto moving = true;// glm::length(currentPosition - collisionObject->GetLastPosition()) > 0.001f;
			const auto id = entity->GetId();

			str << std::setw(8) << std::setfill('0') << std::hex << id;

			if (moving)
			{
				str << "1";

				for (int i = 0; i < 3; i++)
				{
					uint32_t num = *((uint32_t*)&currentPosition[i]);
					str << std::setw(8) << std::setfill('0') << std::hex << num;
				}

				for (int i = 0; i < 3; i++)
				{
					uint32_t num = *((uint32_t*)&currentVelocity[i]);
					str << std::setw(8) << std::setfill('0') << std::hex << num;
				}
			}
			else
			{
				str << "0";
			}
		}

		const auto message = str.str();

		ServerNetworkingManager::Instance()->AddSendMessage(message);
	}
}