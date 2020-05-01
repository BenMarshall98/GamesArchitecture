#pragma once
#include "OpenGLRenderManager.h"

#ifdef GL_430

#include "Shader.h"

class OpenGLShader final : public Shader
{
	int mShaderID;
	
public:
	OpenGLShader(const std::string & pVertexShaderFile, const std::string & pFragmentShaderFile);
	~OpenGLShader();

	OpenGLShader(const OpenGLShader &) = delete;
	OpenGLShader(OpenGLShader &&) = delete;
	OpenGLShader & operator= (const OpenGLShader &) = delete;
	OpenGLShader & operator= (OpenGLShader &&) = delete;

	bool Load() override;
	void Reset() const override;
	void UseProgram() override;

	static int CompileShader(const std::string & pFileName, GLenum pShaderType);
	static bool ReadShader(const std::string & pFileName, std::string & pShaderProgram);
};

#endif