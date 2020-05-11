#pragma once

#include "Entity.h"

class PlaneEntity final : public Entity
{
public:
	PlaneEntity();
	~PlaneEntity() = default;

	PlaneEntity(const PlaneEntity &) = delete;
	PlaneEntity(PlaneEntity&&) = delete;
	PlaneEntity & operator= (const PlaneEntity &) = delete;
	PlaneEntity & operator= (PlaneEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};

