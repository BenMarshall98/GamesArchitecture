#pragma once

#include <glm/vec3.hpp>

#include "Entity.h"

class LargeProjectileEntity final : public Entity
{
public:
	LargeProjectileEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~LargeProjectileEntity() = default;

	LargeProjectileEntity(const LargeProjectileEntity &) = delete;
	LargeProjectileEntity(LargeProjectileEntity&&) = delete;
	LargeProjectileEntity & operator= (const LargeProjectileEntity &) = delete;
	LargeProjectileEntity & operator= (LargeProjectileEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};