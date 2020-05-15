#pragma once

#include "System.h"

class PlaybackSystem final : public System
{
	bool mSimulation = false;
	bool mPlayback = false;

	float mPlaybackTime = 0.0f;
	float mSimulationTime = 0.0f;
	
public:
	PlaybackSystem();
	~PlaybackSystem() = default;

	PlaybackSystem(const PlaybackSystem &) = delete;
	PlaybackSystem(PlaybackSystem&&) = delete;
	PlaybackSystem & operator= (const PlaybackSystem &) = delete;
	PlaybackSystem & operator= (PlaybackSystem&&) = delete;

	void Action(float pDeltaTime) override;

	void StartSimulation()
	{
		mSimulation = true;
		mPlayback = false;
	}

	void StartPlayback()
	{
		mSimulation = false;
		mPlayback = true;
	}

	void StopSimulation()
	{
		mSimulation = false;
		mPlayback = false;
		mPlaybackTime = 0.0f;
		mSimulationTime = 0.0f;
	}

	void SetPlaybackTime(const float pTime)
	{
		mPlaybackTime = pTime;
	}
};

