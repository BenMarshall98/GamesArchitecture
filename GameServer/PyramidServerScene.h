#pragma once
#include <Windows.h>

#include "../GameEngine/PhysicsSystem.h"
#include "../GameEngine/Scene.h"

class PyramidServerScene final : public Scene
{
	int mCurrentSizePyramid = 3;
	int mNextSizePyramid = 3;

	bool mSimulation = false;
	float mSimulationTime = 0.0f;
	float mPlaybackTime = 0.0f;

	int mPlaybackSpeed = 9;
	const float mPlaybackSpeeds[12] = { -4.0f, -2.0f, -1.0f, -0.5f, -0.25f, -0.1f, 0.1f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f };

	bool mPlayback = false;
	bool mPlaybackPlay = true;

	bool mReset = true;

	std::shared_ptr<PhysicsSystem> mPhysicsSystem;
	
	void Reset();
	
public:
	PyramidServerScene() = default;
	~PyramidServerScene() = default;

	PyramidServerScene(const PyramidServerScene&) = delete;
	PyramidServerScene(PyramidServerScene&&) = delete;
	PyramidServerScene& operator= (const PyramidServerScene&) = delete;
	PyramidServerScene& operator= (PyramidServerScene&&) = delete;

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float pDeltaTime) override;
	void Swap() override;

	bool GetSimulation() const
	{
		return mSimulation;
	}

	float GetSimulationTime() const
	{
		return mSimulationTime;
	}

	void StartSimulation()
	{
		mSimulation = true;
		mPhysicsSystem->StartSimulation();
	}

	void StartPlayback()
	{
		mSimulation = false;
		mPlayback = true;
		mPhysicsSystem->StopSimulation();
	}

	int SetReset()
	{
		mReset = true;

		return mNextSizePyramid;
	}

	int IncreasePyramidSize()
	{
		mNextSizePyramid++;

		if (mNextSizePyramid > 50)
		{
			mNextSizePyramid = 50;
		}

		return mNextSizePyramid;
	}

	int DecreasePyramidSize()
	{
		mNextSizePyramid--;

		if (mNextSizePyramid < 3)
		{
			mNextSizePyramid = 3;
		}

		return mNextSizePyramid;
	}

	int IncreasePlaybackSpeed()
	{
		mPlaybackSpeed++;

		if (mPlaybackSpeed >= ARRAYSIZE(mPlaybackSpeeds))
		{
			mPlaybackSpeed = ARRAYSIZE(mPlaybackSpeeds) - 1;
		}

		return mPlaybackSpeed;
	}

	int DecreasePlaybackSpeed()
	{
		mPlaybackSpeed--;

		if (mPlaybackSpeed < 0)
		{
			mPlaybackSpeed = 0;
		}

		return mPlaybackSpeed;
	}

	void PausePlayback()
	{
		mPlaybackPlay = false;
	}

	void UnpausePlayback()
	{
		mPlaybackPlay = true;
	}
};

