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
	std::vector<std::string> messages = ClientNetworkingManager::Instance()->GetRecievedMessages();
	
	//Go Through Networking Messages make list for playback
	std::multimap<uint32_t, Playback> playbackTimeStamps;

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

			auto time = 0.0f;

			{
				const auto val = messages[i].substr(offset, 8);

				uint32_t num;
				std::istringstream str(val);
				str >> std::hex >> num;

				time = *((float*)&num);

				offset += 8;
			}

			for (int j = offset; j < messages.size();)
			{
				uint32_t id;

				{
					const auto val = messages[i].substr(offset, 8);
					std::istringstream str(val);
					str >> std::hex >> id;

					offset += 8;
				}

				const auto moving = messages[i].substr(offset, 1);

				offset++;
				
				if (moving == "0")
				{
					playbackTimeStamps.insert(std::pair<uint32_t, Playback>(id,
						{ glm::vec3(0.0f), glm::vec3(0.0f), time, false }));
				}
				else
				{
					glm::vec3 position;

					for (int k = 0; k < 3; k++)
					{
						const auto val = messages[i].substr(offset, 8);

						uint32_t num;
						std::istringstream str(val);
						str >> std::hex >> num;

						position[k] = *((float*)&num);

						offset += 8;
					}

					glm::vec3 velocity;

					for (int k = 0; k < 3; k++)
					{
						const auto val = messages[i].substr(offset, 8);

						uint32_t num;
						std::istringstream str(val);
						str >> std::hex >> num;

						velocity[k] = *((float*)&num);

						offset += 8;
					}

					playbackTimeStamps.insert(std::pair<uint32_t, Playback>(id,
						{ position, velocity, time, true }));
				}
			}
		}
	}

	//Update System accounting for any new objects
	System::Action(pDeltaTime);
	
	for (auto & entity : mEntities)
	{
		const auto playbackComponent = std::dynamic_pointer_cast<PlaybackComponent>(entity->GetComponentByType(ComponentType::PLAYBACK));

		const auto id = entity->GetId();
		
		const auto playbackValues = playbackTimeStamps.equal_range(id);

		for (auto it = playbackValues.first; it != playbackValues.second; ++it)
		{
			playbackComponent->AddPlayback(it->second);
		}
	}

}