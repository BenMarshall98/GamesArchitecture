#pragma once
#include "PhysicsTree.h"

class Octree final : public PhysicsTree
{
	std::unique_ptr<Octree> mChildren[8];
	std::vector<std::shared_ptr<CollisionObject>> mCollisionObjects;
	std::vector<Octree *> mNeighbours;
	Octree * mParent;

	glm::vec3 mCenter;
	glm::vec3 mSize;

	bool mChecked = false;

	void MoveCollisionObject(const std::shared_ptr<CollisionObject> &pCollisionObject);
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

	bool AddCollisionObject(const std::shared_ptr<CollisionObject>& pCollisionObject) override;
	void RemoveCollisionObject(const std::shared_ptr<CollisionObject>& pCollisionObject) override;
	void UpdateTree() override;
	void GetPossibleCollisions(std::vector<PossibleCollision> & pPossibleCOllisions) override;
};

