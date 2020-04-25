#pragma once

#include "RenderManager.h"

#ifdef DX_11

class DirectXRenderManager final : public RenderManager
{
	friend RenderManager;

	DirectXRenderManager() = default;

public:
	~DirectXRenderManager() = default;

	DirectXRenderManager(const DirectXRenderManager &) = delete;
	DirectXRenderManager(DirectXRenderManager &&) = delete;
	DirectXRenderManager & operator= (const DirectXRenderManager &) = delete;
	DirectXRenderManager & operator= (DirectXRenderManager &&) = delete;

	std::shared_ptr<Model> CreateModel(const std::string& pModel) override;
	std::shared_ptr<Texture> CreateTexture(const std::string& pTexture) override;
	std::shared_ptr<VertexShader> CreateVertexShader(const std::string& pVertexShader) override;
	std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string& pFragmentShader) override;
	std::shared_ptr<Shader> CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader) override;
};

#endif