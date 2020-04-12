#include "System.h"

System::System(const std::vector<ComponentType> & pComponentTypes) : mComponentTypes(pComponentTypes)
{
}

void System::Action(float pDeltaTime)
{
	mEntities.insert(mEntities.end(), mNewEntities.begin(), mNewEntities.end());

	for (const auto& removeEntity : mRemoveEntities)
	{
		const auto it = std::find(mEntities.begin(), mEntities.end(), removeEntity);

		if (it != mEntities.end())
		{
			mEntities.erase(it);
		}
	}
}

void System::AddEntity(const std::shared_ptr<Entity>& pEntity)
{
	if (pEntity->HasComponents(mComponentTypes))
	{
		mNewEntities.push_back(pEntity);
	}
}

void System::UpdateEntity(const std::shared_ptr<Entity>& pEntity)
{
	if (!pEntity->HasComponents(mComponentTypes))
	{
		const auto it = std::find(mEntities.begin(), mEntities.end(), pEntity);

		if (it != mEntities.end())
		{
			mRemoveEntities.push_back(pEntity);
		}
	}
	else
	{
		const auto it = std::find(mEntities.begin(), mEntities.end(), pEntity);

		if (it == mEntities.end())
		{
			mNewEntities.push_back(pEntity);
		}
	}
}