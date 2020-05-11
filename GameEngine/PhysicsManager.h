#pragma once

#include <memory>
#include <vector>

#include "CollisionObject.h"
#include "PhysicsTree.h"

class PhysicsManager
{
	PhysicsManager() = default;
	static PhysicsManager * mInstance;

	std::unique_ptr<PhysicsTree> mPhysicsTree;

	std::vector<std::shared_ptr<CollisionObject>> mInfiniteCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mStaticCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mDynamicCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mAddInfiniteCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mAddStaticCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mAddDynamicCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mRemoveInfiniteCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mRemoveStaticCollisionObjects;
	std::vector<std::shared_ptr<CollisionObject>> mRemoveDynamicCollisionObjects;
	std::vector<CollisionObject *> mNonTreeCollisionObjects;
	
public:
	~PhysicsManager() = default;

	static PhysicsManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new PhysicsManager();
		}

		return mInstance;
	}

	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager(PhysicsManager&&) = delete;
	PhysicsManager& operator= (const PhysicsManager&) = delete;
	PhysicsManager& operator= (PhysicsManager&&) = delete;

	void SetPhysicsTree(std::unique_ptr<PhysicsTree> pPhysicsTree)
	{
		mPhysicsTree = std::move(pPhysicsTree);
	}

	void Update(float pDeltaTime);

	void AddStaticCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mAddStaticCollisionObjects.push_back(pCollisionObject);
	}

	void AddDynamicCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mAddDynamicCollisionObjects.push_back(pCollisionObject);
	}

	void AddInfiniteCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mAddInfiniteCollisionObjects.push_back(pCollisionObject);
	}

	void RemoveStaticCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mRemoveStaticCollisionObjects.push_back(pCollisionObject);
	}

	void RemoveDynamicCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mRemoveDynamicCollisionObjects.push_back(pCollisionObject);
	}

	void RemoveInfiniteCollisionObject(const std::shared_ptr<CollisionObject> & pCollisionObject)
	{
		mRemoveInfiniteCollisionObjects.push_back(pCollisionObject);
	}

	void Reset();

	void AddNonTreeCollisionObject(CollisionObject * pCollisionObject)
	{
		mNonTreeCollisionObjects.push_back(pCollisionObject);
	}
};

