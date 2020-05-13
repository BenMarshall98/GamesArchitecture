#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include "ClientNetworkingManager.h"

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
#include "ThreadingManager.h"
#include "UserInterfaceManager.h"


int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto client = ClientNetworkingManager::Instance();

	IpAddress address(7500, "127.0.0.1");

	if (!client->StartListening(address))
	{
		return -1;
	}
	
	const auto window = Win32Window::Instance(pHInstance, pCmdShow);
	window->Run();
	const auto render = RenderManager::Instance();

	SceneManager::Instance()->Run(std::make_shared<PyramidScene>());

	delete UserInterfaceManager::Instance();
	
	client->CloseConnection();
	
	delete render;
	delete window;
	delete client;

	ThreadingManager::Instance()->CloseAllThreads();
	delete ThreadingManager::Instance();

	return 0;
}
