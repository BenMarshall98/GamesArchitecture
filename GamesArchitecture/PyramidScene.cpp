#include "PyramidScene.h"

#include <DirectXColors.h>


#include "CameraManager.h"
#include "ConstantBuffer.h"
#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "DearImGui/imgui_impl_win32.h"
#include "Dx11Render.h"
#include "EntityManager.h"
#include "InputSystem.h"
#include "ModelLoader.h"
#include "PyramidShapeEntity.h"
#include "RenderSystem.h"
#include "SystemManager.h"
#include "UserEntity.h"

void PyramidScene::Load()
{
	auto systemManager = SystemManager::Instance();

	auto inputSystem = std::make_unique<InputSystem>();
	systemManager->AddUpdateSystem(std::move(inputSystem));

	auto renderSystem = std::make_unique<RenderSystem>();
	systemManager->AddRenderSystem(std::move(renderSystem));

	auto entityManager = EntityManager::Instance();

	entityManager->AddEntity(std::make_shared<UserEntity>(glm::vec3(0.0f, 0.0f, 5.0f)));
	entityManager->AddEntity(std::make_shared<PyramidShapeEntity>(glm::vec3(0.0f), true));

	CameraManager::Instance()->SetPerspective(0.1f, 100.0f);
}

void PyramidScene::Render()
{
	const auto render = Dx11Render::instance();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Current Size of Pyramid %i. Size of Pyramid After Reset %i", mCurrentSizePyramid, mNextSizePyramid);
	ImGui::End();

	ImGui::Render();

	render->clearRenderTargetView(DirectX::Colors::CornflowerBlue);

	EntityManager::Instance()->Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	render->present();
}

void PyramidScene::Update(const float pDeltaTime)
{
	//Check Key Presses

	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('R');

		if (delay <= 0.0f && status)
		{
			delay = 0.5f;
			Reset();
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('T');

		if (delay <= 0.0f && status)
		{
			delay = 0.1f;
			mNextSizePyramid++;

			if (mNextSizePyramid > 50)
			{
				mNextSizePyramid = 50;
			}
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	{
		static auto delay = 0.0f;
		delay -= pDeltaTime;

		const auto status = Win32Window::Instance()->GetKeyStatus('G');

		if (delay <= 0.0f && status)
		{
			delay = 0.1f;
			mNextSizePyramid--;

			if (mNextSizePyramid < 3)
			{
				mNextSizePyramid = 3;
			}
		}
		else if (!status)
		{
			delay = 0.0f;
		}
	}

	EntityManager::Instance()->Update(pDeltaTime);
}

void PyramidScene::Unload()
{

}

void PyramidScene::Reset()
{
	mCurrentSizePyramid = mNextSizePyramid;
}
