#pragma once

#include "System.h"

class PlaybackSystem final : public System
{
public:
	PlaybackSystem();
	~PlaybackSystem() = default;

	PlaybackSystem(const PlaybackSystem &) = delete;
	PlaybackSystem(PlaybackSystem&&) = delete;
	PlaybackSystem & operator= (const PlaybackSystem &) = delete;
	PlaybackSystem & operator= (PlaybackSystem&&) = delete;

	void Action(float pDeltaTime) override;
};

