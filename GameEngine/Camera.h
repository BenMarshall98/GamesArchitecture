#pragma once

#include "glm/glm.hpp"

class Camera
{
protected:
	glm::mat4 mViewMatrix;
	glm::vec3 mUpDirection;
	glm::vec3 mEyePosition;
	glm::vec3 mTargetPosition;
	
public:
	Camera(const glm::vec3 & pEyePosition, const glm::vec3 & pUpDirection, const glm::vec3 & pTargetPosition);
	~Camera() = default;

	Camera(const Camera &) = delete;
	Camera(Camera&&) = delete;
	Camera & operator= (const Camera &) = delete;
	Camera & operator= (Camera&&) = delete;

	glm::mat4 GetViewMatrix() const
	{
		return mViewMatrix;
	}

	glm::vec3 GetViewPosition() const
	{
		return mEyePosition;
	}
};

