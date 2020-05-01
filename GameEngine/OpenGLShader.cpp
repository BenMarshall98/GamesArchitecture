#include "OpenGLShader.h"

#ifdef GL_430

#include "OpenGLVertexShader.h"
#include "OpenGLFragmentShader.h"
#include <fstream>
#include <sstream>

OpenGLShader::OpenGLShader(const std::string& pVertexShaderFile, const std::string& pFragmentShaderFile) :
	Shader(pVertexShaderFile, pFragmentShaderFile)
{
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(mShaderID);
}

bool OpenGLShader::Load()
{
	if (!Shader::Load())
	{
		return false;
	}
	
	const auto vertexShader = std::dynamic_pointer_cast<OpenGLVertexShader>(mVertexShader)->GetShaderID();
	const auto fragmentShader = std::dynamic_pointer_cast<OpenGLFragmentShader>(mFragmentShader)->GetShaderID();
	
	mShaderID = glCreateProgram();
	
	glAttachShader(mShaderID, vertexShader);
	glAttachShader(mShaderID, fragmentShader);
	
	glLinkProgram(mShaderID);
	
	int success;
	glGetProgramiv(mShaderID, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		return false;
	}
	
	glDetachShader(mShaderID, vertexShader);
	glDetachShader(mShaderID, fragmentShader);
	
	return true;
}

void OpenGLShader::Reset() const
{
	glDeleteProgram(mShaderID);
}

void OpenGLShader::UseProgram()
{
	static Shader * lastShader = nullptr;

	if (this != lastShader)
	{
		glUseProgram(mShaderID);
		lastShader = this;
	}
}

int OpenGLShader::CompileShader(const std::string & pFileName, const GLenum pShaderType)
{
	std::string shaderProgram;
	int success;

	if (!ReadShader(pFileName, shaderProgram))
	{
		return -1;
	}
	
	const int shader = glCreateShader(pShaderType);
	const char * program = shaderProgram.c_str();
	glShaderSource(shader, 1, &program, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		return -1;
	}

	return shader;
}

bool OpenGLShader::ReadShader(const std::string & pFileName, std::string & pShaderProgram)
{
	std::ifstream reader(pFileName.c_str());

	if (reader.fail())
	{
		return false;
	}

	std::ostringstream buffer;

	buffer << reader.rdbuf();
	pShaderProgram = buffer.str();
	reader.close();

	return true;
}

#endif