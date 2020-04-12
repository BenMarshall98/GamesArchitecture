#include "ResourceManager.h"

ResourceManager * ResourceManager::mInstance = nullptr;

std::shared_ptr<VertexShader> ResourceManager::LoadVertexShader(const std::string& pVertexShaderFile)
{
	const auto it = mVertexShaders.find(pVertexShaderFile);

	if (it != mVertexShaders.end())
	{
		return it->second;
	}

	auto vertexShader = std::make_shared<VertexShader>(pVertexShaderFile);

	if (vertexShader->Load())
	{
		mVertexShaders.insert(std::pair<std::string, std::shared_ptr<VertexShader>>(pVertexShaderFile, vertexShader));

		return vertexShader;
	}

	return nullptr;
}

std::shared_ptr<FragmentShader> ResourceManager::LoadFragmentShader(const std::string& pFragmentShaderFile)
{
	const auto it = mFragmentShaders.find(pFragmentShaderFile);

	if (it != mFragmentShaders.end())
	{
		return it->second;
	}

	auto fragmentShader = std::make_shared<FragmentShader>(pFragmentShaderFile);

	if (fragmentShader->Load())
	{
		mFragmentShaders.insert(std::pair<std::string, std::shared_ptr<FragmentShader>>(pFragmentShaderFile, fragmentShader));

		return fragmentShader;
	}

	return nullptr;
}

std::shared_ptr<Shader> ResourceManager::LoadShader(const std::string& pVertexShader, const std::string& pFragmentShader)
{
	const auto concat = pVertexShader + pFragmentShader;

	const auto it = mShaders.find(concat);

	if (it != mShaders.end())
	{
		return it->second;
	}

	auto shader = std::make_shared<Shader>(pVertexShader, pFragmentShader);

	if (shader->Load())
	{
		mShaders.insert(std::pair<std::string, std::shared_ptr<Shader>>(concat, shader));

		return shader;
	}

	return nullptr;
}

std::shared_ptr<Texture> ResourceManager::LoadTexture(const std::string& pTextureFile)
{
	const auto it = mTextures.find(pTextureFile);

	if (it != mTextures.end())
	{
		return it->second;
	}

	auto texture = std::make_shared<Texture>(pTextureFile);
	
	if (texture->Load())
	{
		mTextures.insert(std::pair<std::string, std::shared_ptr<Texture>>(pTextureFile, texture));
	
		return texture;
	}

	return nullptr;
}

std::shared_ptr<Model> ResourceManager::LoadModel(const std::string& pModelFile)
{
	const auto it = mModels.find(pModelFile);

	if (it != mModels.end())
	{
		return it->second;
	}

	auto model = std::make_shared<Model>(pModelFile);
	
	if (model->Load())
	{
		mModels.insert(std::pair<std::string, std::shared_ptr<Model>>(pModelFile, model));
	
		return model;
	}

	return nullptr;
}