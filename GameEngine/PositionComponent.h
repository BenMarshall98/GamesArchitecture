#pragma once

#include "Component.h"
#include "glm/glm.hpp"

class PositionComponent final : public Component
{
	glm::vec3 mRenderPosition;
	glm::vec3 mUpdatePosition;
	glm::vec3 mScale;

public:
	PositionComponent(const glm::vec3 & pPosition, const glm::vec3 & pScale);
	~PositionComponent() = default;

	PositionComponent(const PositionComponent &) = delete;
	PositionComponent(PositionComponent&&) = delete;
	PositionComponent & operator= (const PositionComponent &) = delete;
	PositionComponent & operator= (PositionComponent &&) = delete;

	void Swap() override;

	glm::vec3 GetScale() const
	{
		return mScale;
	}

	glm::vec3 GetRenderPosition() const
	{
		return mRenderPosition;
	}

	glm::vec3 GetUpdatePosition() const
	{
		return mUpdatePosition;
	}

	void SetUpdatePosition(const glm::vec3 & pPosition)
	{
		mUpdatePosition = pPosition;
	}
};

