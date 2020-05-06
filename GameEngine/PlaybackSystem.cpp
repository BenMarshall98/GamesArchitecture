#include "PlaybackSystem.h"


#include "PhysicsComponent.h"
#include "PlaybackComponent.h"
#include "PositionComponent.h"

PlaybackSystem::PlaybackSystem() :
	System({ComponentType::PHYSICS, ComponentType::POSITION, ComponentType::PLAYBACK})
{
}

void PlaybackSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	if (mSimulation)
	{
		for (auto & entity : mEntities)
		{
			const auto playbackComponent = std::dynamic_pointer_cast<PlaybackComponent>(entity->GetComponentByType(ComponentType::PLAYBACK));
			const auto physicsComponent = std::dynamic_pointer_cast<PhysicsComponent>(entity->GetComponentByType(ComponentType::PHYSICS));
			const auto positionComponent = std::dynamic_pointer_cast<PositionComponent>(entity->GetComponentByType(ComponentType::POSITION));

			const auto playbackValues = playbackComponent->GetPlaybackAtTime(mSimulationTime);

			const auto playbackTime0 = std::get<0>(playbackValues);
			const auto playbackTime1 = std::get<1>(playbackValues);
			
			if (playbackTime0.mTime == playbackTime1.mTime)
			{
				continue;
			}

			const auto position0 = playbackTime0.mPosition;
			const auto velocity0 = playbackTime0.mVelocity;
			const auto time0 = playbackTime0.mTime;

			const auto position1 = playbackTime1.mPosition;
			const auto velocity1 = playbackTime1.mVelocity;
			const auto time1 = playbackTime1.mTime;

			const auto time = (mSimulationTime - time0) / time1 - time0;
			const auto time2 = pow(time, 2);
			const auto time3 = pow(time, 3);

			glm::vec3 position;
			
			{
				const auto h0 = 2.0f * time3 - 3.0f * time2 + 1.0f;
				const auto h1 = -2.0f * time3 + 3.0f * time2;
				const auto h2 = time3 - 2.0f * time2 + time;
				const auto h3 = time3 - time2;

				position = position0 * h0 + velocity0 * h1 + position1 * h2 + velocity1 * h3;
			}

			glm::vec3 velocity;
			
			{
				const auto h0 = 6 * time2 - 6 * time;
				const auto h2 = -6 * time2 + 6 * time;
				const auto h1 = 3 * time2 - 2 * time + 1;
				const auto h3 = 3 * time2 - 2 * time;

				velocity = position0 * h0 + velocity0 * h1 + position1 * h2 + velocity1 * h3;
			}
			
			const auto collisionObject = physicsComponent->GetCollisionObject();

			position = mix(collisionObject->GetCurrentPosition(), position, 0.1f);
			velocity = mix(collisionObject->GetCurrentVelocity(), velocity, 0.1f);
			
			collisionObject->SetLastVelocity(velocity);
			collisionObject->SetCurrentVelocity(velocity);
			collisionObject->SetLastPosition(position);
			collisionObject->SetCurrentPosition(position);

			positionComponent->SetUpdatePosition(position);
		}
		
		mSimulationTime += pDeltaTime;
	}
	else if (mPlayback)
	{
		//TODO: Deal with rendering
		
		for (auto & entity : mEntities)
		{
			const auto playbackComponent = std::dynamic_pointer_cast<PlaybackComponent>(entity->GetComponentByType(ComponentType::PLAYBACK));
			const auto positionComponent = std::dynamic_pointer_cast<PositionComponent>(entity->GetComponentByType(ComponentType::POSITION));

			const auto playbackValues = playbackComponent->GetPlaybackAtTime(mSimulationTime);

			const auto playbackTime0 = std::get<0>(playbackValues);
			const auto playbackTime1 = std::get<1>(playbackValues);

			const auto position0 = playbackTime0.mPosition;
			const auto velocity0 = playbackTime0.mVelocity;
			const auto time0 = playbackTime0.mTime;

			const auto position1 = playbackTime1.mPosition;
			const auto velocity1 = playbackTime1.mVelocity;
			const auto time1 = playbackTime1.mTime;

			const auto time = (mSimulationTime - time0) / time1 - time0;
			const auto time2 = pow(time, 2);
			const auto time3 = pow(time, 3);

			const auto h0 = 2.0f * time3 - 3.0f * time2 + 1.0f;
			const auto h1 = -2.0f * time3 + 3.0f * time2;
			const auto h2 = time3 - 2.0f * time2 + time;
			const auto h3 = time3 - time2;

			const auto position = position0 * h0 + velocity0 * h1 + position1 * h2 + velocity1 * h3;

			positionComponent->SetUpdatePosition(position);
		}
	}
	
}
