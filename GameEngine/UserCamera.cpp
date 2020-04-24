#include "UserCamera.h"

#include "glm/gtc/matrix_transform.hpp"

UserCamera::UserCamera(const glm::vec3 & pEyePosition, const glm::vec3 & pUpDirection, const glm::vec3 & pTargetPosition, const float pAngleSpeed, const float pMovementSpeed) :
	Camera(pEyePosition, pUpDirection, pTargetPosition), mUpdateViewMatrix(mViewMatrix), mUpdateUpDirection(pUpDirection),
	mUpdateEyePosition(pEyePosition), mUpdateTargetPosition(pTargetPosition), mAngleSpeed(pAngleSpeed), mMovementSpeed(pMovementSpeed)
{
}

void UserCamera::RotateLeftRight(const float pDeltaTime, const bool pLeft)
{
	auto angleChange = mAngleSpeed * pDeltaTime;

	if (pLeft)
	{
		angleChange = -angleChange;
	}

	const auto zAxis = normalize(mUpdateTargetPosition - mUpdateEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpdateUpDirection));
	const auto yAxis = cross(zAxis, xAxis);

	const auto leftRightMat = rotate(glm::mat4(1.0f), glm::radians(angleChange), yAxis);

	mUpdateTargetPosition = mUpdateEyePosition + glm::vec3(leftRightMat * glm::vec4(zAxis, 0.0f));
}

void UserCamera::RotateUpDown(const float pDeltaTime, const bool pUp)
{
	auto angleChange = mAngleSpeed * pDeltaTime;

	if (!pUp)
	{
		angleChange = -angleChange;
	}

	const auto zAxis = normalize(mUpdateTargetPosition - mUpdateEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpdateUpDirection));

	const auto leftRightMat = rotate(glm::mat4(1.0f), glm::radians(angleChange), xAxis);

	mUpdateTargetPosition = mUpdateEyePosition + glm::vec3(leftRightMat * glm::vec4(zAxis, 0.0f));
	mUpdateUpDirection = glm::vec3(leftRightMat * glm::vec4(mUpdateUpDirection, 0.0f));
}

void UserCamera::PanLeftRight(const float pDeltaTime, const bool pLeft)
{
	auto movementChange = mMovementSpeed * pDeltaTime;

	if (!pLeft)
	{
		movementChange = -movementChange;
	}

	const auto zAxis = normalize(mUpdateTargetPosition - mUpdateEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpdateUpDirection));

	const auto movement = xAxis * movementChange;

	mUpdateEyePosition = mUpdateEyePosition + movement;
	mUpdateTargetPosition = mUpdateTargetPosition + movement;
}

void UserCamera::PanUpDown(const float pDeltaTime, const bool pUp)
{
	auto movementChange = mMovementSpeed * pDeltaTime;

	if (!pUp)
	{
		movementChange = -movementChange;
	}

	const auto zAxis = normalize(mUpdateTargetPosition - mUpdateEyePosition);
	const auto xAxis = normalize(cross(zAxis, mUpdateUpDirection));
	const auto yAxis = cross(zAxis, xAxis);

	const auto movement = yAxis * movementChange;

	mUpdateEyePosition = mUpdateEyePosition + movement;
	mUpdateTargetPosition = mUpdateTargetPosition + movement;
}

void UserCamera::PanForwardBackward(const float pDeltaTime, const bool pForward)
{
	auto movementChange = mMovementSpeed * pDeltaTime;

	if (!pForward)
	{
		movementChange = -movementChange;
	}

	const auto zAxis = normalize(mUpdateTargetPosition - mUpdateEyePosition);
	const auto movement = zAxis * movementChange;

	mUpdateEyePosition = mUpdateEyePosition + movement;
	mUpdateTargetPosition = mUpdateTargetPosition + movement;
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

	if (mPanLeft && !mPanRight)
	{
		PanLeftRight(pDeltaTime, true);
	}
	else if (!mPanLeft && mPanRight)
	{
		PanLeftRight(pDeltaTime,false);
	}

	if (mPanUp && !mPanDown)
	{
		PanUpDown(pDeltaTime, true);
	}
	else if (!mPanUp && mPanDown)
	{
		PanUpDown(pDeltaTime, false);
	}

	if (mPanForward && !mPanBackward)
	{
		PanForwardBackward(pDeltaTime, true);
	}
	else if (!mPanForward && mPanBackward)
	{
		PanForwardBackward(pDeltaTime, false);
	}

	mUpdateViewMatrix = lookAt(mUpdateEyePosition, mUpdateTargetPosition, mUpdateUpDirection);
}

void UserCamera::Swap()
{
	mViewMatrix = mUpdateViewMatrix;
	mUpDirection = mUpdateUpDirection;
	mEyePosition = mUpdateEyePosition;
	mTargetPosition = mUpdateTargetPosition;
}