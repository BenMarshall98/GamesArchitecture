#pragma once

#include "System.h"

class PhysicsSystem final : public System
{
public:
	PhysicsSystem();
	~PhysicsSystem() = default;

	PhysicsSystem(const PhysicsSystem &) = delete;
	PhysicsSystem(PhysicsSystem&&) = delete;
	PhysicsSystem & operator= (const PhysicsSystem &) = delete;
	PhysicsSystem & operator= (PhysicsSystem&&) = delete;

	void Action(float pDeltaTime) override;
};

