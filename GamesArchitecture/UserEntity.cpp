#include "UserEntity.h"

#include <Windows.h>

#include "CameraManager.h"
#include "InputComponent.h"

UserEntity::UserEntity(const glm::vec3& pPosition) :
	mCamera(std::make_shared<UserCamera>(
		pPosition, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 15.0f, 1.0f))
{
	CameraManager::Instance()->SetCamera(mCamera);

	std::vector<Input> inputs;

	//Rotate Left
	{
		const Input input = {
			'A',
			VK_CONTROL,
			false,
			true,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->RotateLeft(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Rotate Right
	{
		const Input input = {
			'D',
			VK_CONTROL,
			false,
			true,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->RotateRight(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Rotate Up
	{
		const Input input = {
			'W',
			VK_CONTROL,
			false,
			true,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->RotateUp(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Rotate Down
	{
		const Input input = {
			'S',
			VK_CONTROL,
			false,
			true,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->RotateDown(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Left
	{
		const Input input = {
			'A',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				
				mCamera->PanLeft(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Right
	{
		const Input input = {
			'D',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->PanRight(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Up
	{
		const Input input = {
			'W',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->PanUp(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Down
	{
		const Input input = {
			'S',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->PanDown(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Forward
	{
		const Input input = {
			'Q',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->PanForward(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	//Pan Backward
	{
		const Input input = {
			'E',
			VK_CONTROL,
			false,
			false,
			[this](bool pKeyPressed, float pDeltaTime)
			{
				mCamera->PanBackward(pKeyPressed);
			}
		};

		inputs.push_back(input);
	}

	AddComponent(std::make_shared<InputComponent>(inputs), false);
}

void UserEntity::Update(const float pDeltaTime)
{
	mCamera->Update(pDeltaTime);
}

void UserEntity::Render()
{
	//Do Nothing
}

void UserEntity::Swap()
{
	Entity::Swap();
	mCamera->Swap();
}

void UserEntity::Message(Entity* pEntity, const std::string& pMessage)
{
	//Do Nothing
}
