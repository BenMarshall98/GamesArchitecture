#pragma once
#include <memory>
#include <vector>


#include "CollisionObject.h"

struct PossibleCollision
{
	CollisionObject * mCollisionObject1;
	CollisionObject * mCollisionObject2;
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
	
	virtual bool AddCollisionObject(CollisionObject * pCollisionObject) = 0;
	virtual bool RemoveCollisionObject(CollisionObject * pCollisionObject) = 0;
	virtual void UpdateTree() = 0;
	virtual void GetPossibleCollisions(std::vector<PossibleCollision> & pPossibleCOllisions) = 0;
	virtual void Reset() = 0;
};

