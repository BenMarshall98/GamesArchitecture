#include "UserCamera.h"

#include "glm/gtc/matrix_transform.hpp"

UserCamera::UserCamera(const glm::vec3 & pEyePosition, const glm::vec3 & pUpDirection, const glm::vec3 & pTargetPosition, const float pAngleSpeed, const float pMovementSpeed) :
	Camera(pEyePosition, pUpDirection, pTargetPosition), mAngleSpeed(pAngleSpeed), mMovementSpeed(pMovementSpeed)
{
}

void UserCamera::RotateLeftRight(const float pDeltaTime, bool pLeft)
{
	auto angleChange = mAngleSpeed * pDeltaTime;

	if (pLeft)
	{
		angleChange = -angleChange;
	}

	const auto zAxis = normalize(mTargetPosition - mEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpDirection));
	const auto yAxis = cross(zAxis, xAxis);

	const auto leftRightMat = rotate(glm::mat4(1.0f), glm::radians(angleChange), yAxis);

	mTargetPosition = mEyePosition + glm::vec3(leftRightMat * glm::vec4(zAxis, 0.0f));
}

void UserCamera::RotateUpDown(const float pDeltaTime, const bool pUp)
{
	auto angleChange = mAngleSpeed * pDeltaTime;

	if (!pUp)
	{
		angleChange = -angleChange;
	}

	const auto zAxis = normalize(mTargetPosition - mEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpDirection));

	const auto leftRightMat = rotate(glm::mat4(1.0f), glm::radians(angleChange), xAxis);

	mTargetPosition = mEyePosition + glm::vec3(leftRightMat * glm::vec4(zAxis, 0.0f));
	mUpDirection = glm::vec3(leftRightMat * glm::vec4(mUpDirection, 0.0f));
}

void UserCamera::PanForwardBackward(const float pDeltaTime, const bool pForward)
{
	auto movementChange = mMovementSpeed * pDeltaTime;

	if (!pForward)
	{
		movementChange = -movementChange;
	}

	const auto zAxis = normalize(mTargetPosition - mEyePosition);
	const auto movement = zAxis * movementChange;

	mEyePosition = mEyePosition + movement;
	mTargetPosition = mTargetPosition + movement;
}

void UserCamera::Update(const float pDeltaTime)
{
	if (mRotateLeft && !mRotateRight)
	{
		RotateLeftRight(pDeltaTime, true);
	}
	else if (!mRotateLeft && mRotateRight)
	{
		RotateLeftRight(pDeltaTime, false);
	}

	if (mRotateUp && !mRotateDown)
	{
		RotateUpDown(pDeltaTime, true);
	}
	else if (!mRotateUp && mRotateDown)
	{
		RotateUpDown(pDeltaTime, false);
	}

	if (mPanForward && !mPanBackward)
	{
		PanForwardBackward(pDeltaTime, true);
	}
	else if (!mPanForward && mPanBackward)
	{
		PanForwardBackward(pDeltaTime, false);
	}

	mViewMatrix = lookAt(mEyePosition, mTargetPosition, mUpDirection);
}