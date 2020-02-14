#include "Win32Window.h"
#include <string>

Win32Window * Win32Window::mInstance = nullptr;

Win32Window::Win32Window(const HINSTANCE pHInstance, const int pCmdShow) : mCmdShow(pCmdShow)
{
	WNDCLASSEX wndClassEx;
	wndClassEx.cbSize = sizeof(WNDCLASSEX);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc = windowProcedure;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = pHInstance;
	wndClassEx.hIcon = LoadIcon(pHInstance, IDI_APPLICATION);
	wndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClassEx.hbrBackground = nullptr;
	wndClassEx.lpszMenuName = nullptr;
	wndClassEx.lpszClassName = mClassName;
	wndClassEx.hIconSm = LoadIcon(pHInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wndClassEx))
	{

	}

	RECT rect = { 0, 0, mWidth, mHeight };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	mHwnd = CreateWindow(mClassName, "Games Architecture and Concurrency ACW",
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, pHInstance, nullptr);

	if (!mHwnd)
	{

	}
}

Win32Window * Win32Window::instance()
{
	return mInstance;
}

Win32Window * Win32Window::instance(const HINSTANCE pHInstance, const int pCmdShow)
{
	if (!mInstance)
	{
		mInstance = new Win32Window(pHInstance, pCmdShow);
	}

	return mInstance;
}

LRESULT CALLBACK Win32Window::windowProcedure(const HWND pHwnd, const UINT pMessage, const WPARAM pWParam, const LPARAM pLParam)
{
	PAINTSTRUCT paintStruct;
	HDC hdc;

	switch (pMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(pHwnd, &paintStruct);
		EndPaint(pHwnd, &paintStruct);
		break;
	case WM_CLOSE:
		DestroyWindow(pHwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(pHwnd, pMessage, pWParam, pLParam);
	}

	return 0;
}

bool Win32Window::windowEvents()
{
	auto result = true;

	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			result = false;
		}
	}

	return result;
}