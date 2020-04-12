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
	const auto window = Win32Window::instance();

	mModel = std::make_shared<ModelInstanced>();
	ModelLoader::LoadModelFromFile("Assets/Models/sphere.obj", mModel);

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
		static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
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
	ImGui::End();

	ImGui::Render();

	render->clearRenderTargetView(DirectX::Colors::CornflowerBlue);

	mVertexShader->UseProgram();
	mFragmentShader->UseProgram();

	mModel->render(42925);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	render->present();
}

void PyramidScene::Update(float pDeltaTime)
{

}

void PyramidScene::Unload()
{

}