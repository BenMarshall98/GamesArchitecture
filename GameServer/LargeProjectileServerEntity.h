#pragma once

#include <glm/vec3.hpp>

#include "../GameEngine/Entity.h"

class LargeProjectileServerEntity final : public Entity
{
public:
	LargeProjectileServerEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~LargeProjectileServerEntity() = default;

	LargeProjectileServerEntity(const LargeProjectileServerEntity &) = delete;
	LargeProjectileServerEntity(LargeProjectileServerEntity&&) = delete;
	LargeProjectileServerEntity & operator= (const LargeProjectileServerEntity &) = delete;
	LargeProjectileServerEntity & operator= (LargeProjectileServerEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
};