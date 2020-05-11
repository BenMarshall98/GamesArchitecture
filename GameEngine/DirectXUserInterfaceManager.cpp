#include "DirectXUserInterfaceManager.h"

#ifdef DX_11

#include "DearImGui/imgui_impl_dx11.h"
#include "DirectXRenderManager.h"
#include "RenderManager.h"

DirectXUserInterfaceManager::DirectXUserInterfaceManager()
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
}

DirectXUserInterfaceManager::~DirectXUserInterfaceManager()
{
	ImGui_ImplDX11_Shutdown();
}

void DirectXUserInterfaceManager::NewFrame()
{
	ImGui_ImplDX11_NewFrame();
	UserInterfaceManager::NewFrame();
}

void DirectXUserInterfaceManager::Render()
{
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

#endif