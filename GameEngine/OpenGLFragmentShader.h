#pragma once

#ifdef GL_430

#include "FragmentShader.h"

class OpenGLFragmentShader final : public FragmentShader
{
	int mFragmentShader;

public:
	OpenGLFragmentShader(const std::string & pFilename) : FragmentShader(pFilename) {}
	~OpenGLFragmentShader();

	OpenGLFragmentShader(const OpenGLFragmentShader &) = delete;
	OpenGLFragmentShader(OpenGLFragmentShader &&) = delete;
	OpenGLFragmentShader & operator= (const OpenGLFragmentShader &) = delete;
	OpenGLFragmentShader & operator= (OpenGLFragmentShader &&) = delete;

	bool Load() override;
	void Reset() override;
	void UseProgram() override;

	int GetShaderID() const
	{
		return mFragmentShader;
	}
};

#endif