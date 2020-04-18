#pragma once
#include <memory>
#include <vector>


#include "CollisionObject.h"

struct PossibleCollision
{
	std::shared_ptr<CollisionObject> mCollisionObject1;
	std::shared_ptr<CollisionObject> mCollisionObject2;
};

class PhysicsTree
{
public:
	PhysicsTree() = default;
	virtual ~PhysicsTree() = default;

	PhysicsTree(const PhysicsTree&) = delete;
	PhysicsTree(PhysicsTree&&) = delete;
	PhysicsTree& operator= (const PhysicsTree&) = delete;
	PhysicsTree& operator= (PhysicsTree&&) = delete;
	
	virtual bool AddCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject) = 0;
	virtual void RemoveCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject) = 0;
	virtual void UpdateTree() = 0;
	virtual void GetPossibleCollisions(std::vector<PossibleCollision> & pPossibleCOllisions) = 0;
};

