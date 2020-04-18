#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(const glm::vec3& pEyePosition, const glm::vec3& pUpDirection, const glm::vec3& pTargetPosition) :
	mEyePosition(pEyePosition), mUpDirection(pUpDirection), mTargetPosition(pTargetPosition), mViewMatrix(lookAt(pEyePosition, pTargetPosition, pUpDirection))
{
}