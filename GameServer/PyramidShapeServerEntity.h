#pragma once

#include <glm/vec3.hpp>

#include "../GameEngine/Entity.h"

class PyramidShapeServerEntity final : public Entity
{
public:
	PyramidShapeServerEntity(const glm::vec3 & pPosition, bool pBase);
	~PyramidShapeServerEntity() = default;

	PyramidShapeServerEntity(const PyramidShapeServerEntity &) = delete;
	PyramidShapeServerEntity(PyramidShapeServerEntity&&) = delete;
	PyramidShapeServerEntity & operator= (const PyramidShapeServerEntity &) = delete;
	PyramidShapeServerEntity & operator= (PyramidShapeServerEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};