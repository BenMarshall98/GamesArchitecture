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

	if (!mResetComplete)
	{
		mResetComplete = mResetCount == ServerNetworkingManager::Instance()->NumberOfConnections();
	}
	
	//Go Through Networking Messages
	for (int i = 0; i < messages.size(); i++)
	{
		const auto idMessage = messages[i].substr(1, 1);

		const auto id = std::stoi(idMessage);

		messages[i] = messages[i].substr(2);
		
		auto offset = 0;

		if (messages[i] == "ResetPyramid")
		{
			const auto size = mScene->SetReset();

			mResetCount = 0;
			mResetComplete = false;

			std::ostringstream str;
			str << "RPyr" << std::setw(2) << std::setfill('0') << size;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			continue;
		}
		if (messages[i] == "ResetComplete")
		{
			mResetCount++;
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
			mScene->StepBackPlayback();

			ServerNetworkingManager::Instance()->AddSendMessage("StepBackPlayback");

			continue;
		}
		if (messages[i] == "StepUpPlayback")
		{
			mScene->StepUpPlayback();

			ServerNetworkingManager::Instance()->AddSendMessage("StepUpPlayback");

			continue;
		}
		
		const auto type = messages[i].substr(offset, 4);

		//TODO: Playback controls and other messages
		if (type == "AddP" && mResetComplete)
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

	if (mScene->GetSimulationTime() > 60.0f && mScene->GetSimulation())
	{
		std::ostringstream str;
		str << "SPla";

		const auto simulationTime = mScene->GetSimulationTime();
		uint32_t num = *((uint32_t*)&simulationTime);
		str << std::setw(8) << std::setfill('0') << std::hex << num;
		
		const auto message = str.str();

		ServerNetworkingManager::Instance()->AddSendMessage(message);
		
		mScene->StartPlayback();
	}

	if (mScene->GetSimulation())
	{
		auto moving = false;
		const auto simulationTime = mScene->GetSimulationTime();

		for (int i = 0; i < mEntities.size() / 100 + 1; i++)
		{
			std::ostringstream str;
			str << "Time";

			uint32_t num = *((uint32_t*)&simulationTime);
			str << std::setw(8) << std::setfill('0') << std::hex << num;

			for (int j = i * 100; j < mEntities.size() && j < (i + 1) * 100; j++)
			{
				const auto physicsComponent = std::dynamic_pointer_cast<PhysicsComponent>(mEntities[j]->GetComponentByType(ComponentType::PHYSICS));

				const auto collisionObject = physicsComponent->GetCollisionObject();

				if (collisionObject->GetType() == RigidBodyType::STATIC)
				{
					continue;
				}

				const auto currentPosition = collisionObject->GetCurrentPosition();
				const auto currentVelocity = collisionObject->GetCurrentVelocity();

				//TODO: Check epsilon

				const auto length = glm::length(currentPosition - collisionObject->GetLastPosition());
				
				moving |= length > FLT_EPSILON;

				if (!moving)
				{
					int i = 0;
				}
				
				const auto id = mEntities[j]->GetId();

				str << std::setw(8) << std::setfill('0') << std::hex << id;

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
			}

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
		}

		static auto count = 0;

		if (moving)
		{
			count = 0;
		}
		else
		{
			count++;
		}

		if (count > 10)
		{
			std::ostringstream str;
			str << "SPla";
			
			uint32_t num = *((uint32_t*)&simulationTime);
			str << std::setw(8) << std::setfill('0') << std::hex << num;

			const auto message = str.str();

			ServerNetworkingManager::Instance()->AddSendMessage(message);
			
			mScene->StartPlayback();
		}
	}
}