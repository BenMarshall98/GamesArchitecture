#pragma once

#include "../GameEngine/Entity.h"

class PlaneServerEntity final : public Entity
{
public:
	PlaneServerEntity();
	~PlaneServerEntity() = default;

	PlaneServerEntity(const PlaneServerEntity &) = delete;
	PlaneServerEntity(PlaneServerEntity&&) = delete;
	PlaneServerEntity & operator= (const PlaneServerEntity &) = delete;
	PlaneServerEntity & operator= (PlaneServerEntity &&) = delete;

	void Update(float pDeltaTime) override;
	void Render() override;
	void Message(Entity* pEntity, const std::string& pMessage) override;
};

