#pragma once

#include <memory>

#include "CollisionObject.h"
#include "Component.h"

class PhysicsComponent final : public Component
{
	std::shared_ptr<CollisionObject> mCollisionObject;

public:
	explicit PhysicsComponent(const std::shared_ptr<CollisionObject> & pCollisionObject);
	~PhysicsComponent();

	PhysicsComponent(const PhysicsComponent &) = delete;
	PhysicsComponent(PhysicsComponent&&) = delete;
	PhysicsComponent & operator= (const PhysicsComponent &) = delete;
	PhysicsComponent & operator= (PhysicsComponent &&) = delete;

	void Swap() override;

	std::shared_ptr<CollisionObject> GetCollisionObject() const
	{
		return mCollisionObject;
	}
};

