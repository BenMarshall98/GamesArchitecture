#include "PlaybackSystem.h"

PlaybackSystem::PlaybackSystem() :
	System({ComponentType::PHYSICS, ComponentType::POSITION, ComponentType::PLAYBACK})
{
}

void PlaybackSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	//TODO: Lock Playback

	//TODO: Get all Playback at current time

	//TODO: Unlock Playback

	//TODO: Deal with physics from playback
}
