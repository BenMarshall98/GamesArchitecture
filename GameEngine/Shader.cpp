#include "Shader.h"

#include "ResourceManager.h"

bool Shader::Load()
{
	mVertexShader = ResourceManager::Instance()->LoadVertexShader(mVertexShaderFile);
	mFragmentShader = ResourceManager::Instance()->LoadFragmentShader(mFragmentShaderFile);

	return mVertexShader && mFragmentShader;
}

void Shader::Reset() const
{
	mVertexShader->Reset();
	mFragmentShader->Reset();
}

void Shader::UseProgram()
{
	static Shader * lastShader = nullptr;

	if (lastShader != this)
	{
		mVertexShader->UseProgram();
		mFragmentShader->UseProgram();

		lastShader = this;
	}
}