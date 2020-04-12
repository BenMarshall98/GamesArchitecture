#pragma once

#include <memory>

#include "Component.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class RenderComponent final : public Component
{
	std::shared_ptr<Shader> mShader;
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;

public:
	RenderComponent(const std::shared_ptr<Shader> & pShader, const std::shared_ptr<Model> & pModel, const std::shared_ptr<Texture> & pTexture);
	~RenderComponent() = default;

	RenderComponent(const RenderComponent &) = delete;
	RenderComponent(RenderComponent&&) = delete;
	RenderComponent & operator= (const RenderComponent &) = delete;
	RenderComponent & operator= (RenderComponent &&) = delete;

	void Swap() override;

	std::shared_ptr<Shader> GetShader() const
	{
		return mShader;
	}

	std::shared_ptr<Model> GetModel() const
	{
		return mModel;
	}

	std::shared_ptr<Texture> GetTexture() const
	{
		return mTexture;
	}
};

