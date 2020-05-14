#pragma once

#include "ConstantBuffer.h"
#include "System.h"
#include "glm/glm.hpp"

struct ModelMatrix
{
	glm::mat4 mModel;
};

struct ViewProjectionMatrix
{
	glm::mat4 mView;
	glm::mat4 mProjection;
};

class RenderSystem final : public System
{
	std::unique_ptr<ConstantBuffer<ViewProjectionMatrix>> mViewBuffer;
	
public:
	RenderSystem();
	~RenderSystem() = default;

	RenderSystem(const RenderSystem &) = delete;
	RenderSystem(RenderSystem&&) = delete;
	RenderSystem & operator= (const RenderSystem &) = delete;
	RenderSystem & operator= (RenderSystem&&) = delete;

	void Action(float pDeltaTime) override;
};