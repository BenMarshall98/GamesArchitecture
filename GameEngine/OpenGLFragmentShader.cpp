#include "OpenGLFragmentShader.h"

#ifdef GL_430

#include "OpenGL.h"
#include "OpenGLShader.h"

OpenGLFragmentShader::~OpenGLFragmentShader()
{
	glDeleteShader(mFragmentShader);
}

bool OpenGLFragmentShader::Load()
{
	mFragmentShader = OpenGLShader::CompileShader(mFilename, GL_FRAGMENT_SHADER);

	if (mFragmentShader == -1)
	{
		return false;
	}

	return true;
}

void OpenGLFragmentShader::Reset()
{
	glDeleteShader(mFragmentShader);
}

void OpenGLFragmentShader::UseProgram()
{
	//Do Nothing
}
#endif