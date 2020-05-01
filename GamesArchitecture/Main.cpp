#include "Win32Window.h"
#include "RenderManager.h"
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>

#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_win32.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "DearImGui/imgui_impl_opengl3.h"

#include "DirectXRenderManager.h"

#include "PyramidScene.h"
#include "SceneManager.h"


int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::Instance(pHInstance, pCmdShow);
	window->Run();
	const auto render = RenderManager::Instance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto & io = ImGui::GetIO(); (void)io;
	
	ImGui::StyleColorsDark();
	
	ImGui_ImplWin32_Init(window->GetHwnd());

#ifdef DX_11
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
#elif GL_430
	ImGui_ImplOpenGL3_Init();
#endif

	SceneManager::Instance()->Run(std::make_shared<PyramidScene>());

	//ImGui_ImplDX11_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete render;
	delete window;

	return 0;
}
