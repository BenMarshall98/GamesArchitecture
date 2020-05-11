#pragma once

#include "UserInterfaceManager.h"

#ifdef GL_430

class OpenGLUserInterfaceManager final : public UserInterfaceManager
{
	friend UserInterfaceManager;

	OpenGLUserInterfaceManager();

public:
	~OpenGLUserInterfaceManager();

	OpenGLUserInterfaceManager(const OpenGLUserInterfaceManager &) = delete;
	OpenGLUserInterfaceManager(OpenGLUserInterfaceManager &&) = delete;
	OpenGLUserInterfaceManager & operator= (const OpenGLUserInterfaceManager &) = delete;
	OpenGLUserInterfaceManager & operator= (OpenGLUserInterfaceManager &&) = delete;

	void NewFrame() override;
	void Render() override;
};

#endif