#pragma once

#include <string>

#include "DearImGui/imgui.h"

class OpenGLUserInterfaceManager;
class DirectXUserInterfaceManager;

class UserInterfaceManager
{
	friend OpenGLUserInterfaceManager;
	friend DirectXUserInterfaceManager;

	static UserInterfaceManager * mInstance;
	UserInterfaceManager();

public:
	virtual ~UserInterfaceManager();
	static UserInterfaceManager * Instance();

	UserInterfaceManager(const UserInterfaceManager &) = delete;
	UserInterfaceManager(UserInterfaceManager &&) = delete;
	UserInterfaceManager & operator= (const UserInterfaceManager &) = delete;
	UserInterfaceManager & operator= (UserInterfaceManager &&) = delete;

	virtual void NewFrame();
	
	void EndFrame() const
	{
		ImGui::End();
		ImGui::Render();
	}

	virtual void Render() = 0;
};

