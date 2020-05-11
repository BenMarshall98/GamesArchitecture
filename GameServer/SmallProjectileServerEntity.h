#pragma once

#include <glm/vec3.hpp>

#include "../GameEngine/Entity.h"

class SmallProjectileServerEntity final : public Entity
{
public:
	SmallProjectileServerEntity(const glm::vec3 & pPosition, const glm::vec3 & pVelocity);
	~SmallProjectileServerEntity() = default;

	SmallProjectileServerEntity(const SmallProjectileServerEntity &) = delete;
	SmallProjectileServerEntity(SmallProjectileServerEntity&&) = delete;
	SmallProjectileServerEntity & operator= (const SmallProjectileServerEntity &) = delete;
	SmallProjectileServerEntity & operator= (SmallProjectileServerEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};