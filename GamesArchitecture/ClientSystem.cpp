#include "ClientSystem.h"

//#include "ClientNetworkingManager.h"
#include <map>
#include <sstream>

#include "ClientNetworkingManager.h"
#include "EntityManager.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "PlaybackComponent.h"
#include "SmallProjectileEntity.h"
#include "LargeProjectileEntity.h"
#include "GrenageProjectileEntity.h"

//TODO

ClientSystem::ClientSystem(PyramidScene* pScene) :
	System({ComponentType::PHYSICS, ComponentType::POSITION, ComponentType::PLAYBACK}), mScene(pScene)
{
}

void ClientSystem::Action(const float pDeltaTime)
{
	//Get Networking Messages
	std::vector<std::string> messages = ClientNetworkingManager::Instance()->GetRecieveMessages();
	
	//TODO: Go Through Networking Messages make list for playback
	std::multimap<uint16_t, Playback> playbackTimeStamps;

	for (int i = 0; i < messages.size(); i++)
	{
		auto offset = 0;
		const auto type = messages[i].substr(offset, 1);

		//TODO: Playback controls and other messages
		if (type == "AddP")
		{
			const auto projectileType = messages[i].substr(offset += 1, 4);

			offset += 4;

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
				EntityManager::Instance()->AddEntity(std::make_shared<SmallProjectileEntity>(position, velocity));
			}
			else if (projectileType == "L")
			{
				EntityManager::Instance()->AddEntity(std::make_shared<LargeProjectileEntity>(position, velocity));
			}
			else if (projectileType == "G")
			{
				EntityManager::Instance()->AddEntity(std::make_shared<GrenageProjectileEntity>(position, velocity));
			}
		}
		else if (type == "Time")
		{
			auto offset = 0;
		}
	}

	//Update System accounting for any new objects
	System::Action(pDeltaTime);
	
	//TODO: Lock Playback

	//TODO: Populate Playback System

	//TODO: Unlock Playback
}