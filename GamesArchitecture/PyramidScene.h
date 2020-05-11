#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FragmentShader.h"
#include "ModelInstanced.h"
#include "PhysicsSystem.h"
#include "PlaybackSystem.h"
#include "Scene.h"
#include "VertexShader.h"
#include "UserEntity.h"

enum class ProjectileType
{
	SMALL,
	LARGE,
	GRENADE,
	NONE
};

class PyramidScene final : public Scene
{
	int mCurrentSizePyramid = 3;
	int mNextSizePyramid = 3;
	bool mMainCamera = false;

	bool mSimulation = false;
	float mSimulationTime = 0.0f;
	float mPlaybackTime = 0.0f;
	float mDisplaySimulationTime = 0.0f;
	float mDisplayPlaybackTime = 0.0f;

	int mPlaybackSpeed = 9;
	int mDisplayPlaybackSpeed = 9;
	const float mPlaybackSpeeds[12] = {-4.0f, -2.0f, -1.0f, -0.5f, -0.25f, -0.1f, 0.1f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f};

	bool mPlayback = false;
	bool mPlaybackPlay = true;

	ProjectileType mProjectile = ProjectileType::SMALL;
	bool mReset = false;

	std::shared_ptr<PlaybackSystem> mPlaybackSystem;
	std::shared_ptr<PhysicsSystem> mPhysicsSystem;
	
	void Reset();

public:
	PyramidScene() = default;
	~PyramidScene() = default;

	PyramidScene(const PyramidScene&) = delete;
	PyramidScene(PyramidScene&&) = delete;
	PyramidScene& operator= (const PyramidScene&) = delete;
	PyramidScene& operator= (PyramidScene&&) = delete;

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float pDeltaTime) override;
	void Swap() override;

	void StartSimulation()
	{
		mSimulation = true;
		mSimulationTime = 0.0f;
		mPlaybackTime = 0.0f;
		mPlaybackSystem->StartSimulation();
		mPhysicsSystem->StartSimulation();
	}

	void StartPlayback()
	{
		mPlayback = true;
		mSimulation = false;
		mPhysicsSystem->StopSimulation();
		mPlaybackSystem->StartPlayback();
		mSimulationTime = 0.0f;
		mPlaybackTime = 0.0f;
	}

	void PausePlayback()
	{
		mPlaybackPlay = false;
	}

	void UnpausePlayback()
	{
		mPlaybackPlay = true;
	}

	void SetPyramidSize(const int pSize)
	{
		mNextSizePyramid = pSize;
	}

	void SetPlaybackSpeed(const int pSpeed)
	{
		mPlaybackSpeed = pSpeed;
	}

	void StepBackPlayback()
	{
		mPlaybackTime -= 0.1f;

		if (mPlaybackTime < 0.0f)
		{
			mPlaybackTime = 0.0f;
		}
	}

	void StepUpPlayback()
	{
		mPlaybackTime += 0.1f;

		//TODO: Max time

		if (mPlaybackTime > 4.0f)
		{
			mPlaybackTime = 4.0f;
		}
	}
};