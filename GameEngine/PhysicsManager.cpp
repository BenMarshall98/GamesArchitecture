#include "PhysicsManager.h"

PhysicsManager * PhysicsManager::mInstance = nullptr;

void PhysicsManager::Update(float pDeltaTime)
{
	mStaticCollisionObjects.insert(mStaticCollisionObjects.end(), mAddStaticCollisionObjects.begin(), mAddStaticCollisionObjects.end());
	mDynamicCollisionObjects.insert(mDynamicCollisionObjects.end(), mAddDynamicCollisionObjects.begin(), mAddDynamicCollisionObjects.end());

	for (int i = 0; i < mAddStaticCollisionObjects.size(); i++)
	{
		mPhysicsTree->AddCollisionObject(mAddStaticCollisionObjects[i].get());
	}
	
	for (int i = 0; i < mAddDynamicCollisionObjects.size(); i++)
	{
		mPhysicsTree->AddCollisionObject(mAddDynamicCollisionObjects[i].get());
	}

	for (int i = 0; i < mRemoveStaticCollisionObjects.size(); i++)
	{
		mPhysicsTree->RemoveCollisionObject(mRemoveStaticCollisionObjects[i].get());
	}

	for (int i = 0; i < mRemoveDynamicCollisionObjects.size(); i++)
	{
		mPhysicsTree->RemoveCollisionObject(mRemoveDynamicCollisionObjects[i].get());
	}
	
	for (const auto& removeStaticCollisionObject : mRemoveStaticCollisionObjects)
	{
		const auto it = std::find(mStaticCollisionObjects.begin(), mStaticCollisionObjects.end(), removeStaticCollisionObject);

		if (it != mStaticCollisionObjects.end())
		{
			mStaticCollisionObjects.erase(it);
		}
	}

	for (const auto& removeDynamicCollisionObject : mRemoveDynamicCollisionObjects)
	{
		const auto it = std::find(mDynamicCollisionObjects.begin(), mDynamicCollisionObjects.end(), removeDynamicCollisionObject);

		if (it != mDynamicCollisionObjects.end())
		{
			mDynamicCollisionObjects.erase(it);
		}
	}

	mAddStaticCollisionObjects.clear();
	mAddDynamicCollisionObjects.clear();
	mRemoveStaticCollisionObjects.clear();
	mRemoveDynamicCollisionObjects.clear();

	mAddStaticCollisionObjects.shrink_to_fit();
	mAddDynamicCollisionObjects.shrink_to_fit();
	mRemoveStaticCollisionObjects.shrink_to_fit();
	mRemoveDynamicCollisionObjects.shrink_to_fit();

	mPhysicsTree->UpdateTree();

	for (auto& dynamicCollisionObject : mDynamicCollisionObjects)
	{
		dynamicCollisionObject->Update(pDeltaTime);
	}

	static std::vector<PossibleCollision> possibleCollisions;

	possibleCollisions.clear();

	mPhysicsTree->GetPossibleCollisions(possibleCollisions);

	possibleCollisions.shrink_to_fit();

	std::vector<CollisionData> collisions;

	for (int i = 0; i < possibleCollisions.size(); i++)
	{
		CollisionData data;

		if(possibleCollisions[i].mCollisionObject1->Collision(possibleCollisions[i].mCollisionObject2, data))
		{
			collisions.push_back(data);
		}
	}

	for (int i = 0; i < collisions.size(); i++)
	{
		CollisionObject::CollisionResponse(collisions[i]);
	}
	
	for (auto& dynamicCollisionObject : mDynamicCollisionObjects)
	{
		dynamicCollisionObject->Swap();
	}
}

void PhysicsManager::Reset()
{
	mPhysicsTree->Reset();
	
	mStaticCollisionObjects.clear();
	mDynamicCollisionObjects.clear();
	mAddStaticCollisionObjects.clear();
	mAddDynamicCollisionObjects.clear();
	mRemoveStaticCollisionObjects.clear();
	mRemoveDynamicCollisionObjects.clear();

	mStaticCollisionObjects.shrink_to_fit();
	mDynamicCollisionObjects.shrink_to_fit();
	mAddStaticCollisionObjects.shrink_to_fit();
	mAddDynamicCollisionObjects.shrink_to_fit();
	mRemoveStaticCollisionObjects.shrink_to_fit();
	mRemoveDynamicCollisionObjects.shrink_to_fit();
}
