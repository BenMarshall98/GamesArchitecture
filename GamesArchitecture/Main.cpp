#include "Win32Window.h"
#include "Dx11Render.h"
#include <DirectXColors.h>
#include <memory>

#include "ModelLoader.h"
#include "Model.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ConstantBuffer.h"

#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_win32.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "ModelInstanced.h"

struct ModelMatrix
{
	DirectX::XMFLOAT4X4 mModel;
};

struct ViewProjectionMatrix
{
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProjection;
};

int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::instance(pHInstance, pCmdShow);
	window->run();
	const auto render = Dx11Render::instance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO & io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window->getHwnd());

	{
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Dx11Render::instance()->getDevice(device);

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
		Dx11Render::instance()->getDeviceContext(deviceContext);

		ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
	}

	auto model = std::make_shared<ModelInstanced>();
	ModelLoader::loadModelFromFile("Assets/Models/sphere.obj", model);

	auto vertexShader = std::make_unique<VertexShader>(L"SimpleVertexProgram.hlsl");
	auto fragmentShader = std::make_unique<FragmentShader>(L"SimpleFragmentProgram.hlsl");

	auto result = vertexShader->Load();
	result = fragmentShader->Load();

	auto modelBuffer = std::make_unique<ConstantBuffer<ModelMatrix>>(0);
	auto vpBuffer = std::make_unique<ConstantBuffer<ViewProjectionMatrix>>(1);

	modelBuffer->Load();
	vpBuffer->Load();

	ModelMatrix modelMat;

	XMStoreFloat4x4(&modelMat.mModel, DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity()));

	ViewProjectionMatrix vpMat;

	XMStoreFloat4x4(&vpMat.mView, DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(5.0f, 5.0f, 5.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
	)));

	XMStoreFloat4x4(&vpMat.mProjection, DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
		static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
		0.01f, 1000.0f)));

	modelBuffer->UpdateBuffer(modelMat);
	vpBuffer->UpdateBuffer(vpMat);

	while (window->windowEvents())
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, world!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Render();

		render->clearRenderTargetView(DirectX::Colors::CornflowerBlue);

		vertexShader->UseProgram();
		fragmentShader->UseProgram();

		model->render(7000);

		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		render->present();
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete render;
	delete window;

	return 0;
}