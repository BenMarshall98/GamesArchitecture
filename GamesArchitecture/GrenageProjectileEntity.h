#pragma once

#include <glm/vec3.hpp>

#include "Entity.h"

class GrenageProjectileEntity final :public Entity
{
public:
	GrenageProjectileEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~GrenageProjectileEntity() = default;

	GrenageProjectileEntity(const GrenageProjectileEntity &) = delete;
	GrenageProjectileEntity(GrenageProjectileEntity&&) = delete;
	GrenageProjectileEntity & operator= (const GrenageProjectileEntity &) = delete;
	GrenageProjectileEntity & operator= (GrenageProjectileEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
};

