#include "InputComponent.h"

#include "Win32Window.h"

InputComponent::InputComponent(const std::vector<Input>& pInputs) : Component(ComponentType::INPUT), mInputs(pInputs)
{
}

void InputComponent::PlayInputs(const float pDeltaTime)
{
	for (const auto & input : mInputs)
	{
		auto pressed = true;
		
		if(input.mKey1)
		{
			pressed &= !input.mAntiKey1 == Win32Window::Instance()->GetKeyStatus(input.mKey1);
		}

		if(input.mKey2)
		{
			pressed &= !input.mAntiKey2 == Win32Window::Instance()->GetKeyStatus(input.mKey2);
		}

		input.mFunction(pressed, pDeltaTime);
	}
}

void InputComponent::Swap()
{
	//Do Nothing
}