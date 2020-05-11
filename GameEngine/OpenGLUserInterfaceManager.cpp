#include "OpenGLUserInterfaceManager.h"

#ifdef GL_430

#include "DearImGui/imgui_impl_opengl3.h"

OpenGLUserInterfaceManager::OpenGLUserInterfaceManager()
{
	ImGui_ImplOpenGL3_Init();
}

OpenGLUserInterfaceManager::~OpenGLUserInterfaceManager()
{
	ImGui_ImplOpenGL3_Shutdown();
}

void OpenGLUserInterfaceManager::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	UserInterfaceManager::NewFrame();
}

void OpenGLUserInterfaceManager::Render()
{
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#endif