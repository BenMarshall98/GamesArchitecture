#pragma once

#include "Component.h"

#include <glm/vec3.hpp>
#include <mutex>
#include <tuple>
#include <vector>

struct Playback
{
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	float mTime;
	bool mMoving;
};

class PlaybackComponent final : public Component
{
	std::vector<Playback> mPlaybackList;
	
public:	
	PlaybackComponent();
	~PlaybackComponent() = default;

	PlaybackComponent(const PlaybackComponent &) = delete;
	PlaybackComponent(PlaybackComponent&&) = delete;
	PlaybackComponent & operator= (const PlaybackComponent &) = delete;
	PlaybackComponent & operator= (PlaybackComponent&&) = delete;

	void AddPlayback(const Playback & pPlayback);
	
	void Swap() override;

	std::tuple<Playback, Playback> GetPlaybackAtTime(float pTime);
};

