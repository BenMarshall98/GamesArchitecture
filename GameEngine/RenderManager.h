#pragma once
#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class OpenGLRenderManager;
class DirectXRenderManager;

class RenderManager
{
	friend OpenGLRenderManager;
	friend DirectXRenderManager;
	
	static RenderManager * mInstance;
	RenderManager() = default;

public:
	virtual ~RenderManager() = default;
	static RenderManager * Instance();

	RenderManager(const RenderManager &) = delete;
	RenderManager(RenderManager &&) = delete;
	RenderManager & operator= (const RenderManager &) = delete;
	RenderManager & operator= (RenderManager &&) = delete;

	virtual std::shared_ptr<Model> CreateModel(const std::string & pModel) = 0;
	virtual std::shared_ptr<Texture> CreateTexture(const std::string & pTexture) = 0;
	virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::string & pVertexShader) = 0;
	virtual std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string & pFragmentShader) = 0;
	virtual std::shared_ptr<Shader> CreateShader(const std::string & pVertexShader, const std::string & pFragmentShader) = 0;
};

