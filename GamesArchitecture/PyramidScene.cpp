#include "PyramidScene.h"

#include <DirectXColors.h>

#include "ConstantBuffer.h"
#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "DearImGui/imgui_impl_win32.h"
#include "Dx11Render.h"
#include "ModelLoader.h"

void PyramidScene::Load()
{
	const auto window = Win32Window::Instance();

	mVertexShader = std::make_unique<VertexShader>("SimpleVertexProgram.hlsl");
	mFragmentShader = std::make_unique<FragmentShader>("SimpleFragmentProgram.hlsl");

	auto result = mVertexShader->Load();
	result = mFragmentShader->Load();

	auto vpBuffer = std::make_unique<ConstantBuffer<ViewProjectionMatrix>>(1);
	vpBuffer->Load();

	ViewProjectionMatrix vpMat;

	XMStoreFloat4x4(&vpMat.mView, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(5.0f, 5.0f, 5.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
	)));

	XMStoreFloat4x4(&vpMat.mProjection, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
		static_cast<float>(window->GetWidth()) / static_cast<float>(window->GetHeight()),
		0.01f, 1000.0f)));

	vpBuffer->UpdateBuffer(vpMat);
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

	mVertexShader->UseProgram();
	mFragmentShader->UseProgram();

	//mModel->render(42925);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	render->present();
}

void PyramidScene::Update(float pDeltaTime)
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
}

void PyramidScene::Unload()
{

}

void PyramidScene::Reset()
{
	mCurrentSizePyramid = mNextSizePyramid;
}
