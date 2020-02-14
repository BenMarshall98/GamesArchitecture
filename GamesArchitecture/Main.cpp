#include "Win32Window.h"
#include "Dx11Render.h"
#include <DirectXColors.h>

int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::instance(pHInstance, pCmdShow);
	window->run();
	const auto render = Dx11Render::instance();

	while (window->windowEvents())
	{
		render->clearRenderTargetView(DirectX::Colors::CornflowerBlue);
		render->present();
	}

	delete render;
	delete window;

	return 0;
}