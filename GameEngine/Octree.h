#pragma once
#include "PhysicsTree.h"

//TODO: Adapted from simulation ACW

class Octree final : public PhysicsTree
{
	std::unique_ptr<Octree> mChildren[8];
	std::vector<CollisionObject *> mCollisionObjects;
	std::vector<Octree *> mNeighbours;

	glm::vec3 mCenter;
	glm::vec3 mSize;
	
	Octree * mParent;

	bool mChecked = false;

	void MoveCollisionObject(CollisionObject * pCollisionObject);
	void GetNeighbours();
	void DeleteNeighbour(Octree * pNeighbour);
	void FindNeighbour(const glm::vec3 & pCenter, const glm::vec3 & pSize, std::vector<Octree *> & pNeighbours, Octree * pNeighbour);

	int NumOfRigidBodies() const
	{
		return mCollisionObjects.size();
	}

	bool HasChildren() const
	{
		return mChildren[0].get();
	}
	
public:
	Octree(const glm::vec3 & pCenter, const glm::vec3 & pSize, Octree * pParent = nullptr);
	~Octree();

	Octree(const Octree&) = delete;
	Octree(Octree&&) = delete;
	Octree& operator= (const Octree&) = delete;
	Octree& operator= (Octree&&) = delete;

	bool AddCollisionObject(CollisionObject * pCollisionObject) override;
	bool RemoveCollisionObject(CollisionObject * pCollisionObject) override;
	void UpdateTree() override;
	void GetPossibleCollisions(std::vector<PossibleCollision> & pPossibleCOllisions) override;
	void Reset() override;
};

