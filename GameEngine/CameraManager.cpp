#include "CameraManager.h"

#include "Win32Window.h"
#include "glm/gtc/matrix_transform.hpp"

CameraManager * CameraManager::mInstance = nullptr;

void CameraManager::SetCamera(const std::shared_ptr<Camera>& pCamera)
{
	mCamera = pCamera;
}

void CameraManager::SetPerspective(const float pNearPlane, const float pFarPlane)
{
	mNearPlane = pNearPlane;
	mFarPlane = pFarPlane;

	const auto window = Win32Window::Instance();
	const auto height = static_cast<float>(window->GetHeight());
	const auto width = static_cast<float>(window->GetWidth());

	mPerspective = glm::perspectiveFov(glm::radians(45.0f), width, height, mNearPlane, mFarPlane);
}
