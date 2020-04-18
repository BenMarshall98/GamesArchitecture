#pragma once
#include "glm/glm.hpp"
#include <memory>

#include "Camera.h"

class CameraManager
{
	std::shared_ptr<Camera> mCamera;
	std::shared_ptr<Camera> mNextCamera;

	glm::mat4 mPerspective;

	float mNearPlane;
	float mFarPlane;

	static CameraManager * mInstance;
	CameraManager();

public:
	~CameraManager() = default;

	CameraManager(const CameraManager &) = delete;
	CameraManager(CameraManager&&) = delete;
	CameraManager & operator= (const CameraManager &) = delete;
	CameraManager & operator= (CameraManager&&) = delete;

	void SetCamera(const std::shared_ptr<Camera> & pCamera);
	void SetPerspective(float pNearPlane, float pFarPlane);

	glm::mat4 GetPerspectiveMatrix() const
	{
		return mPerspective;
	}

	glm::mat4 GetViewMatrix() const
	{
		if (mCamera)
		{
			return mCamera->GetViewMatrix();
		}

		return glm::mat4(1.0f);
	}

	glm::vec3 GetViewPosition() const
	{
		if (mCamera)
		{
			return mCamera->GetViewPosition();
		}

		return glm::vec3(0.0f);
	}

	float GetNearPlane() const
	{
		return mNearPlane;
	}

	float GetFarPlane() const
	{
		return mFarPlane;
	}
};

