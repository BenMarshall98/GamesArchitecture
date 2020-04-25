#include "Shader.h"

#include "ResourceManager.h"

bool Shader::Load()
{
	mVertexShader = ResourceManager::Instance()->LoadVertexShader(mVertexShaderFile);
	mFragmentShader = ResourceManager::Instance()->LoadFragmentShader(mFragmentShaderFile);

	return mVertexShader && mFragmentShader;
}
