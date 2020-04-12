#include "Win32Window.h"
#include "Dx11Render.h"
#include <DirectXColors.h>
#include <DirectXMath.h>
#include <memory>

#include "DearImGui/imgui.h"
#include "DearImGui/imgui_impl_win32.h"
#include "DearImGui/imgui_impl_dx11.h"
#include "PyramidScene.h"
#include "SceneManager.h"


int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::instance(pHInstance, pCmdShow);
	window->run();
	const auto render = Dx11Render::instance();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto & io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window->getHwnd());

	{
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		Dx11Render::instance()->getDevice(device);

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
		Dx11Render::instance()->getDeviceContext(deviceContext);

		ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());
	}

	SceneManager::Instance()->Run(std::make_shared<PyramidScene>());

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete render;
	delete window;

	return 0;
}
