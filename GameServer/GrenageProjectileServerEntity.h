#pragma once

#include <glm/vec3.hpp>

#include "../GameEngine/Entity.h"

class GrenageProjectileServerEntity final : public Entity
{
	bool mFirst = true;
	bool mExplode = false;
	
public:
	GrenageProjectileServerEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~GrenageProjectileServerEntity() = default;

	GrenageProjectileServerEntity(const GrenageProjectileServerEntity &) = delete;
	GrenageProjectileServerEntity(GrenageProjectileServerEntity&&) = delete;
	GrenageProjectileServerEntity & operator= (const GrenageProjectileServerEntity &) = delete;
	GrenageProjectileServerEntity & operator= (GrenageProjectileServerEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};

