#include "OpenGLVertexShader.h"

#ifdef GL_430

#include "OpenGL.h"
#include "OpenGLShader.h"

OpenGLVertexShader::~OpenGLVertexShader()
{
	glDeleteShader(mVertexShader);
}

bool OpenGLVertexShader::Load()
{
	mVertexShader = OpenGLShader::CompileShader(mFilename, GL_VERTEX_SHADER);

	if (mVertexShader == -1)
	{
		return false;
	}

	return true;
}

void OpenGLVertexShader::Reset()
{
	glDeleteShader(mVertexShader);
}

void OpenGLVertexShader::UseProgram()
{
	//Do Nothing
}

#endif