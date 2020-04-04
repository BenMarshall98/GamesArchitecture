#pragma once

#include <map>
#include <string>

#include "FragmentShader.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexShader.h"

class ResourceManager
{
	friend Shader;
	
	std::map<std::string, std::shared_ptr<Model>> mModels;
	std::map<std::string, std::shared_ptr<VertexShader>> mVertexShaders;
	std::map<std::string, std::shared_ptr<FragmentShader>> mFragmentShaders;
	std::map<std::string, std::shared_ptr<Shader>> mShaders;
	std::map<std::string, std::shared_ptr<Texture>> mTextures;

	std::shared_ptr<VertexShader> LoadVertexShader(const std::string & pVertexShaderFile);
	std::shared_ptr<FragmentShader> LoadFragmentShader(const std::string & pFragmentShaderFile);

	static ResourceManager * mInstance;

	ResourceManager() = default;

public:
	~ResourceManager() = default;

	static ResourceManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new ResourceManager();
		}

		return mInstance;
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager& operator= (ResourceManager&&) = delete;

	std::shared_ptr<Model> LoadModel(const std::string & pModelFile);
	std::shared_ptr<Shader> LoadShader(const std::string & pVertexShader, const std::string & pFragmentShader);
	std::shared_ptr<Texture> LoadTexture(const std::string & pTextureFile);
};

