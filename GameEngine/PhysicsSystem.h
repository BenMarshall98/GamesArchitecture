#pragma once

#include "System.h"

class PhysicsSystem final : public System
{
	bool mSimulation = false;
	
public:
	PhysicsSystem();
	~PhysicsSystem() = default;

	PhysicsSystem(const PhysicsSystem &) = delete;
	PhysicsSystem(PhysicsSystem&&) = delete;

	PhysicsSystem & operator= (const PhysicsSystem &) = delete;
	PhysicsSystem & operator= (PhysicsSystem&&) = delete;

	void Action(float pDeltaTime) override;

	void StartSimulation()
	{
		mSimulation = true;
	}

	void StopSimulation()
	{
		mSimulation = false;
	}
};