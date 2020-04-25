#include "DirectXShader.h"

#ifdef DX_11

#include "ResourceManager.h"

DirectXShader::DirectXShader(const std::string& pVertexShaderFile, const std::string& pFragmentShaderFile) :
	Shader(pVertexShaderFile, pFragmentShaderFile)
{
}

bool DirectXShader::Load()
{
	Shader::Load();

	return mVertexShader && mFragmentShader;
}

void DirectXShader::Reset() const
{
	mVertexShader->Reset();
	mFragmentShader->Reset();
}

void DirectXShader::UseProgram()
{
	static Shader * lastShader = nullptr;

	if (lastShader != this)
	{
		mVertexShader->UseProgram();
		mFragmentShader->UseProgram();

		lastShader = this;
	}
}

#endif