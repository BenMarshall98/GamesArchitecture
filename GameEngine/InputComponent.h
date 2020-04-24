#pragma once
#include <functional>
#include <Windows.h>
#include <vector>

#include "Component.h"

struct Input
{
	WPARAM mKey1 = 0;
	WPARAM mKey2 = 0;
	bool mAntiKey1 = false;
	bool mAntiKey2 = false;
	std::function<void(bool, float)> mFunction;
};

class InputComponent final : public Component
{
	std::vector<Input> mInputs;

public:
	explicit InputComponent(const std::vector<Input> & pInputs);
	~InputComponent() = default;

	InputComponent(const InputComponent &) = delete;
	InputComponent(InputComponent&&) = delete;
	InputComponent & operator= (const InputComponent &) = delete;
	InputComponent & operator= (InputComponent&&) = delete;

	void PlayInputs(float pDeltaTime);

	void Swap() override;
};

