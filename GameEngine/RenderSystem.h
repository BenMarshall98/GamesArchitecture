#pragma once

#include "ConstantBuffer.h"
#include "System.h"
#include "glm/glm.hpp"

struct ModelMatrix
{
	glm::mat4 mModel;
};

class RenderSystem final : public System
{
	ConstantBuffer<ModelMatrix> mModelBuffer;
public:
	RenderSystem();
	~RenderSystem() = default;

	RenderSystem(const RenderSystem &) = delete;
	RenderSystem(RenderSystem&&) = delete;
	RenderSystem & operator= (const RenderSystem &) = delete;
	RenderSystem & operator= (RenderSystem&&) = delete;

	void Action(float pDeltaTime) override;
};