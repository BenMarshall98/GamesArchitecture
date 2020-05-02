#pragma once

#include <glm/vec3.hpp>

#include "Entity.h"

class PyramidShapeEntity final : public Entity
{
public:
	PyramidShapeEntity(const glm::vec3 & pPosition, bool pBase);
	~PyramidShapeEntity() = default;

	PyramidShapeEntity(const PyramidShapeEntity &) = delete;
	PyramidShapeEntity(PyramidShapeEntity&&) = delete;
	PyramidShapeEntity & operator= (const PyramidShapeEntity &) = delete;
	PyramidShapeEntity & operator= (PyramidShapeEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
};

