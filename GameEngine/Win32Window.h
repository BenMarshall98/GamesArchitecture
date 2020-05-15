#pragma once

#define NOMINMAX

#include <map>
#include <Windows.h>

class Win32Window
{
	const char * mClassName = "GamesArchitecture";
	std::map<WPARAM, bool> mStatus;
	HWND mHwnd;
	int mWidth = 800;
	int mHeight = 600;
	int mCmdShow;

	static Win32Window * mInstance;

	Win32Window(HINSTANCE pHInstance, int pCmdShow);
	void SetKeyState(WPARAM pKey, bool pStatus);

	static LRESULT CALLBACK WindowProcedure(HWND pHwnd, UINT pMessage, WPARAM pWParam, LPARAM pLParam);

public:

	static Win32Window * Instance();
	static Win32Window * Instance(HINSTANCE pHInstance, int pCmdShow);

	static bool WindowEvents();

	int GetWidth() const
	{
		return mWidth;
	}

	int GetHeight() const
	{
		return mHeight;
	}

	HWND GetHwnd() const
	{
		return mHwnd;
	}

	void Run() const
	{
		ShowWindow(mHwnd, mCmdShow);
	}

	~Win32Window() = default;

	Win32Window(const Win32Window&) = delete;
	Win32Window(Win32Window &&) = delete;
	Win32Window & operator= (const Win32Window &) = delete;
	Win32Window & operator= (Win32Window &&) = delete;

	bool GetKeyStatus(WPARAM pKey);
};