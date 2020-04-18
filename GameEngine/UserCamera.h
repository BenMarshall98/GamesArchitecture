#pragma once

#include "Camera.h"

class UserCamera final : public Camera
{
	glm::mat4 mUpdateViewMatrix;
	glm::vec3 mUpdateUpDirection;
	glm::vec3 mUpdateEyePosition;
	glm::vec3 mUpdateTargetPosition;
	float mAngleSpeed;
	float mMovementSpeed;
	bool mRotateLeft = false;
	bool mRotateRight = false;
	bool mRotateUp = false;
	bool mRotateDown = false;
	bool mPanForward = false;
	bool mPanBackward = false;

	void RotateLeftRight(float pDeltaTime, bool pLeft = true);
	void RotateUpDown(float pDeltaTime, bool pUp = true);
	void PanForwardBackward(float pDeltaTime, bool pForward = true);

public:
	UserCamera(const glm::vec3 & pEyePosition, const glm::vec3 & pUpDirection, const glm::vec3 & pTargetPosition, float pAngleSpeed, float pMovementSpeed);
	~UserCamera() = default;

	UserCamera(const UserCamera&) = delete;
	UserCamera(UserCamera&&) = delete;
	UserCamera & operator= (const UserCamera&) = delete;
	UserCamera & operator= (UserCamera&&) = delete;

	void RotateLeft(const bool pKeyPressed)
	{
		mRotateLeft = pKeyPressed;
	}

	void RotateRight(const bool pKeyPressed)
	{
		mRotateRight = pKeyPressed;
	}

	void RotateUp(const bool pKeyPressed)
	{
		mRotateUp = pKeyPressed;
	}

	void RotateDown(const bool pKeyPressed)
	{
		mRotateDown = pKeyPressed;
	}

	void PanForward(const bool pKeyPressed)
	{
		mPanForward = pKeyPressed;
	}

	void PanBackward(const bool pKeyPressed)
	{
		mPanBackward = pKeyPressed;
	}


	void Update(float pDeltaTime);
	void Swap();
};

