#include "InputSystem.h"

#include "InputComponent.h"

InputSystem::InputSystem() : System({ComponentType::INPUT})
{
}

void InputSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	for (auto & entity : mEntities)
	{
		const auto inputComponent = std::dynamic_pointer_cast<InputComponent>(entity->GetComponentByType(ComponentType::INPUT));

		inputComponent->PlayInputs(pDeltaTime);
	}
}