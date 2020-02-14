#include "Win32Window.h"

int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::instance(pHInstance, pCmdShow);
	window->run();

	while (window->windowEvents());

	delete window;

	return 0;
}