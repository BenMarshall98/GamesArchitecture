#include "PyramidScene.h"

#include <DirectXColors.h>

#include "CameraManager.h"
#include "ConstantBuffer.h"
#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "DearImGui/imgui_impl_win32.h"
#include "DearImGui/imgui_impl_opengl3.h"
#include "EntityManager.h"
#include "InputSystem.h"
#include "ModelLoader.h"
#include "Octree.h"
#include "PhysicsManager.h"
#include "PhysicsSystem.h"
#include "PyramidShapeEntity.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "SystemManager.h"
#include "UserEntity.h"
#include "Win32Window.h"

void PyramidScene::Load()
{
	auto octree = std::make_unique<Octree>(glm::vec3(0.0f), glm::vec3(1.0f));
	PhysicsManager::Instance()->SetPhysicsTree(std::move(octree));
	
	auto systemManager = SystemManager::Instance();

	auto inputSystem = std::make_unique<InputSystem>();
	systemManager->AddUpdateSystem(std::move(inputSystem));

	auto physicsSystem = std::make_unique<PhysicsSystem>();
	systemManager->AddUpdateSystem(std::move(physicsSystem));

	auto renderSystem = std::make_unique<RenderSystem>();
	systemManager->AddRenderSystem(std::move(renderSystem));

	Reset();

	CameraManager::Instance()->SetPerspective(0.01f, 100.0f);
}

void PyramidScene::Render()
{
	const auto render = RenderManager::Instance();
	//ImGui_ImplDX11_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Current Size of Pyramid %i. Size of Pyramid After Reset %i", mCurrentSizePyramid, mNextSizePyramid);
	ImGui::End();

	ImGui::Render();

	render->ClearRenderTargetView(DirectX::Colors::CornflowerBlue);

	EntityManager::Instance()->Render();

	//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	render->Present();
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

	auto entityManager = EntityManager::Instance();

	entityManager->Reset();

	PhysicsManager::Instance()->Reset();

	entityManager->AddEntity(std::make_shared<UserEntity>(glm::vec3(1.0f, 0.5f, 1.0f)));

	const auto offset = 1.0f / sqrt(2.0f) * 0.02f;

	auto mass = false;

	for (auto i = mCurrentSizePyramid; i >= 1; i--)
	{
		const auto y = static_cast<float>(mCurrentSizePyramid - i) * offset + 0.01f;

		for (auto j = 0; j < i; j++)
		{
			for (auto k = 0; k < i; k++)
			{
				const auto x = j * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;
				const auto z = k * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;

				entityManager->AddEntity(std::make_shared<PyramidShapeEntity>(glm::vec3(x, y, z), mass));
			}
		}

		mass = true;
	}
}
