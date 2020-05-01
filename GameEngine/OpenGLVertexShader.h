#pragma once

#ifdef GL_430

#include "VertexShader.h"

class OpenGLVertexShader final : public VertexShader
{
	int mVertexShader;

public:
	OpenGLVertexShader(const std::string & pFilename) : VertexShader(pFilename) {}
	~OpenGLVertexShader();

	OpenGLVertexShader(const OpenGLVertexShader &) = delete;
	OpenGLVertexShader(OpenGLVertexShader &&) = delete;
	OpenGLVertexShader & operator= (const OpenGLVertexShader &) = delete;
	OpenGLVertexShader & operator= (OpenGLVertexShader &&) = delete;

	bool Load() override;
	void Reset() override;
	void UseProgram() override;

	int GetShaderID() const
	{
		return mVertexShader;
	}
};

#endif