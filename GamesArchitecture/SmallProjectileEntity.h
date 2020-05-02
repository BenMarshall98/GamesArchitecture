#pragma once

#include <glm/vec3.hpp>

#include "Entity.h"

class SmallProjectileEntity final : public Entity
{
public:
	SmallProjectileEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~SmallProjectileEntity() = default;

	SmallProjectileEntity(const SmallProjectileEntity &) = delete;
	SmallProjectileEntity(SmallProjectileEntity&&) = delete;
	SmallProjectileEntity & operator= (const SmallProjectileEntity &) = delete;
	SmallProjectileEntity & operator= (SmallProjectileEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
};