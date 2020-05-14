#pragma once
#include <memory>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include <DirectXMath.h>
#include <map>


#include "ModelInstanced.h"
#include "RenderSystem.h"

class OpenGLRenderManager;
class DirectXRenderManager;

struct RenderSetup
{
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Shader> mShader;
};

class RenderManager
{
	friend OpenGLRenderManager;
	friend DirectXRenderManager;

	std::map<RenderSetup *, std::shared_ptr<Shader>> mInstancedShaders;
	std::map<RenderSetup *, std::vector<std::shared_ptr<ModelInstanced>>> mInstancedModels;
	std::map<RenderSetup *, std::vector<glm::mat4>> mRenderObjects;
	std::unique_ptr<ConstantBuffer<ModelMatrix>> mModelBuffer;
	
	static RenderManager * mInstance;
	RenderManager();

public:
	virtual ~RenderManager() = default;
	static RenderManager * Instance();

	RenderManager(const RenderManager &) = delete;
	RenderManager(RenderManager &&) = delete;
	RenderManager & operator= (const RenderManager &) = delete;
	RenderManager & operator= (RenderManager &&) = delete;

	virtual bool Load() = 0;

	virtual std::shared_ptr<Model> CreateModel(const std::string & pModel) = 0;
	virtual std::shared_ptr<Texture> CreateTexture(const std::string & pTexture) = 0;
	virtual std::shared_ptr<VertexShader> CreateVertexShader(const std::string & pVertexShader) = 0;
	virtual std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string & pFragmentShader) = 0;
	virtual std::shared_ptr<Shader> CreateShader(const std::string & pVertexShader, const std::string & pFragmentShader) = 0;
	virtual std::shared_ptr<ModelInstanced> CreateInstancedModel(const std::string & pModel) = 0;
	
	virtual void ClearRenderTargetView(const DirectX::XMVECTORF32 & pColor) const = 0;
	virtual void Present() const = 0;

	void AddRenderSetup(const std::shared_ptr<Model> & pModel, const std::shared_ptr<Shader> & pShader, const glm::mat4 & pModelMatrix);
	void Render();
};

