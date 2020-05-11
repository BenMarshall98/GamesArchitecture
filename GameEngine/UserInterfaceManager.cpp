#include "UserInterfaceManager.h"


#include "DearImGui/imgui_impl_win32.h"
#include "OpenGLUserInterfaceManager.h"
#include "DirectXUserInterfaceManager.h"
#include "Win32Window.h"

UserInterfaceManager * UserInterfaceManager::mInstance = nullptr;

UserInterfaceManager::UserInterfaceManager()
{
	const auto window = Win32Window::Instance();
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	auto & io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window->GetHwnd());
}

UserInterfaceManager::~UserInterfaceManager()
{
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

UserInterfaceManager* UserInterfaceManager::Instance()
{
	if (!mInstance)
	{
#ifdef GL_430
		mInstance = new OpenGLUserInterfaceManager();
#elif DX_11
		mInstance = new DirectXUserInterfaceManager();
#endif
	}

	return mInstance;
}

void UserInterfaceManager::NewFrame()
{
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}
