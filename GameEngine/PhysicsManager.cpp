#include "PhysicsManager.h"

PhysicsManager * PhysicsManager::mInstance = nullptr;

void PhysicsManager::Update(float pDeltaTime)
{
	mStaticCollisionObjects.insert(mStaticCollisionObjects.end(), mAddStaticCollisionObjects.begin(), mAddStaticCollisionObjects.end());
	mDynamicCollisionObjects.insert(mDynamicCollisionObjects.end(), mAddDynamicCollisionObjects.begin(), mAddDynamicCollisionObjects.end());
	mInfiniteCollisionObjects.insert(mInfiniteCollisionObjects.end(), mAddInfiniteCollisionObjects.begin(), mAddInfiniteCollisionObjects.end());

	for (int i = 0; i < mNonTreeCollisionObjects.size(); i++)
	{
		if (mPhysicsTree->AddCollisionObject(mNonTreeCollisionObjects[i]))
		{
			mNonTreeCollisionObjects.erase(mNonTreeCollisionObjects.begin() + i);
			i--;
		}
	}
	
	for (int i = 0; i < mAddStaticCollisionObjects.size(); i++)
	{
		if (!mPhysicsTree->AddCollisionObject(mAddStaticCollisionObjects[i].get()))
		{
			mNonTreeCollisionObjects.push_back(mAddStaticCollisionObjects[i].get());
		}
	}
	
	for (int i = 0; i < mAddDynamicCollisionObjects.size(); i++)
	{
		//mPhysicsTree->AddCollisionObject(mAddDynamicCollisionObjects[i].get());

		if (!mPhysicsTree->AddCollisionObject(mAddDynamicCollisionObjects[i].get()))
		{
			mNonTreeCollisionObjects.push_back(mAddDynamicCollisionObjects[i].get());
		}
	}

	for (int i = 0; i < mRemoveStaticCollisionObjects.size(); i++)
	{
		mPhysicsTree->RemoveCollisionObject(mRemoveStaticCollisionObjects[i].get());

		for (int j = 0; j < mNonTreeCollisionObjects.size(); j++)
		{
			if (mNonTreeCollisionObjects[j] == mRemoveStaticCollisionObjects[i].get()) 
			{
				mNonTreeCollisionObjects.erase(mNonTreeCollisionObjects.begin() + j);
				break;
			}
		}
	}

	for (int i = 0; i < mRemoveDynamicCollisionObjects.size(); i++)
	{
		mPhysicsTree->RemoveCollisionObject(mRemoveDynamicCollisionObjects[i].get());

		for (int j = 0; j < mNonTreeCollisionObjects.size(); j++)
		{
			if (mNonTreeCollisionObjects[j] == mRemoveDynamicCollisionObjects[i].get())
			{
				mNonTreeCollisionObjects.erase(mNonTreeCollisionObjects.begin() + j);
				break;
			}
		}
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

	for (const auto& removeInfiniteCollisionObject : mRemoveInfiniteCollisionObjects)
	{
		const auto it = std::find(mInfiniteCollisionObjects.begin(), mInfiniteCollisionObjects.end(), removeInfiniteCollisionObject);

		if (it != mInfiniteCollisionObjects.end())
		{
			mInfiniteCollisionObjects.erase(it);
		}
	}

	mAddStaticCollisionObjects.clear();
	mAddDynamicCollisionObjects.clear();
	mAddInfiniteCollisionObjects.clear();
	mRemoveStaticCollisionObjects.clear();
	mRemoveDynamicCollisionObjects.clear();
	mRemoveInfiniteCollisionObjects.clear();

	mAddStaticCollisionObjects.shrink_to_fit();
	mAddDynamicCollisionObjects.shrink_to_fit();
	mAddInfiniteCollisionObjects.shrink_to_fit();
	mRemoveStaticCollisionObjects.shrink_to_fit();
	mRemoveDynamicCollisionObjects.shrink_to_fit();
	mRemoveInfiniteCollisionObjects.shrink_to_fit();

	for (auto& dynamicCollisionObject : mDynamicCollisionObjects)
	{
		dynamicCollisionObject->Swap();
	}

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

	for (int i = 0; i < mInfiniteCollisionObjects.size(); i++)
	{
		for (int j = 0; j < mDynamicCollisionObjects.size(); j++)
		{
			CollisionData data;

			if (mInfiniteCollisionObjects[i]->Collision(mDynamicCollisionObjects[j].get(), data))
			{
				collisions.push_back(data);
			}
		}
	}

	for (int i = 0; i < collisions.size(); i++)
	{
		CollisionObject::CollisionResponse(collisions[i], pDeltaTime);
	}
}

void PhysicsManager::Reset()
{
	mPhysicsTree->Reset();

	mNonTreeCollisionObjects.clear();
	mStaticCollisionObjects.clear();
	mDynamicCollisionObjects.clear();
	mInfiniteCollisionObjects.clear();
	mAddStaticCollisionObjects.clear();
	mAddDynamicCollisionObjects.clear();
	mAddInfiniteCollisionObjects.clear();
	mRemoveStaticCollisionObjects.clear();
	mRemoveDynamicCollisionObjects.clear();
	mRemoveInfiniteCollisionObjects.clear();
	
	mNonTreeCollisionObjects.shrink_to_fit();
	mStaticCollisionObjects.shrink_to_fit();
	mDynamicCollisionObjects.shrink_to_fit();
	mInfiniteCollisionObjects.shrink_to_fit();
	mAddStaticCollisionObjects.shrink_to_fit();
	mAddDynamicCollisionObjects.shrink_to_fit();
	mAddInfiniteCollisionObjects.shrink_to_fit();
	mRemoveStaticCollisionObjects.shrink_to_fit();
	mRemoveDynamicCollisionObjects.shrink_to_fit();
	mRemoveInfiniteCollisionObjects.shrink_to_fit();
}
