#pragma once

#include "RenderManager.h"
#include "wglext.h"

#ifdef GL_430

class OpenGLRenderManager final : public RenderManager
{
	friend RenderManager;

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
	HDC hDc;

	OpenGLRenderManager() = default;

public:
	~OpenGLRenderManager() = default;

	OpenGLRenderManager(const OpenGLRenderManager &) = delete;
	OpenGLRenderManager(OpenGLRenderManager &&) = delete;
	OpenGLRenderManager & operator= (const OpenGLRenderManager &) = delete;
	OpenGLRenderManager & operator= (OpenGLRenderManager &&) = delete;

	bool Load() override;

	std::shared_ptr<Model> CreateModel(const std::string& pModel) override;
	std::shared_ptr<Texture> CreateTexture(const std::string& pTexture) override;
	std::shared_ptr<VertexShader> CreateVertexShader(const std::string& pVertexShader) override;
	std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string& pFragmentShader) override;
	std::shared_ptr<Shader> CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader) override;
	std::shared_ptr<ModelInstanced> CreateInstancedModel(const std::string& pModel) override;

	void ClearRenderTargetView(const DirectX::XMVECTORF32 & pColor) const override;
	void Present() const override;
};

#endif