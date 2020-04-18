#pragma once

#include "System.h"

class InputSystem final : public System
{
public:
	InputSystem();
	~InputSystem() = default;

	InputSystem(const InputSystem &) = delete;
	InputSystem(InputSystem&&) = delete;
	InputSystem & operator= (const InputSystem &) = delete;
	InputSystem & operator= (InputSystem&&) = delete;

	void Action(float pDeltaTime) override;
};

