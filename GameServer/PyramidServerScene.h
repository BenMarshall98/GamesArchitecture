#pragma once
#include "../GameEngine/PhysicsSystem.h"
#include "../GameEngine/Scene.h"

class PyramidServerScene final : public Scene
{
	int mCurrentSizePyramid = 3;
	int mNextSizePyramid = 3;

	bool mSimulation = false;
	float mSimulationTime = 0.0f;
	bool mPlayback = false;

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
};

