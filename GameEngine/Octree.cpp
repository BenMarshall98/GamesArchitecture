#include "Octree.h"

Octree::Octree(const glm::vec3& pCenter, const glm::vec3& pSize, Octree* pParent) : mParent(pParent), mCenter(pCenter), mSize(pSize)
{
}

Octree::~Octree()
{
	for (auto & neighbour : mNeighbours)
	{
		neighbour->DeleteNeighbour(this);
	}
}

bool Octree::AddCollisionObject(CollisionObject * pCollisionObject)
{
	const auto bodyPos = pCollisionObject->GetCurrentPosition();

	if (bodyPos.x < mCenter.x - mSize.x ||
		bodyPos.x > mCenter.x + mSize.x ||
		bodyPos.y < mCenter.y - mSize.y ||
		bodyPos.y > mCenter.y + mSize.y ||
		bodyPos.z < mCenter.z - mSize.z ||
		bodyPos.z > mCenter.z + mSize.z)
	{
		return false;
	}

	if (mSize.x > 0.03 &&
		mSize.y > 0.03 &&
		mSize.z > 0.03)
	{
		if (mChildren[0])
		{
			for (auto & i : mChildren)
			{
				if (i->AddCollisionObject(pCollisionObject))
				{
					break;
				}
			}
		}
		else
		{
			const auto childSize = mSize / 2.0f;
			glm::vec3 centers[8] =
			{
				mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * 1.0f, childSize.z * 1.0f),
				mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * 1.0f, childSize.z * -1.0f),
				mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * -1.0f, childSize.z * 1.0f),
				mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * -1.0f, childSize.z * -1.0f),
				mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * 1.0f, childSize.z * 1.0f),
				mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * 1.0f, childSize.z * -1.0f),
				mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * -1.0f, childSize.z * 1.0f),
				mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * -1.0f, childSize.z * -1.0f)
			};


			auto found = false;
			for (auto i = 0; i < 8; i++)
			{
				mChildren[i] = std::make_unique<Octree>(centers[i], childSize, this);
				if (!found && mChildren[i]->AddCollisionObject(pCollisionObject))
				{
					found = true;
				}
			}

			for (auto& i : mChildren)
			{
				i->GetNeighbours();
			}
		}
	}
	else
	{
		mCollisionObjects.push_back(pCollisionObject);
	}
	return true;
}

bool Octree::RemoveCollisionObject(CollisionObject * pCollisionObject)
{
	for (auto i = 0u; i < mCollisionObjects.size(); i++)
	{
		if (mCollisionObjects[i] == pCollisionObject)
		{
			mCollisionObjects.erase(mCollisionObjects.begin() + i);
			return true;
		}
	}

	if (mChildren[0])
	{
		for (auto& child : mChildren)
		{
			if (child->RemoveCollisionObject(pCollisionObject))
			{
				return true;
			}
		}
	}

	return false;
}

void Octree::UpdateTree()
{
	mChecked = false;
	for (auto i = 0u; i < mCollisionObjects.size(); i++)
	{
		const auto bodyPos = mCollisionObjects[i]->GetCurrentPosition();

		//TODO: Do same check in physics system
		if (isnan(bodyPos.x))
		{
			mCollisionObjects.erase(mCollisionObjects.begin() + i);
			i--;
			continue;;
		}

		if (bodyPos.x < mCenter.x - mSize.x ||
			bodyPos.x > mCenter.x + mSize.x ||
			bodyPos.y < mCenter.y - mSize.y ||
			bodyPos.y > mCenter.y + mSize.y ||
			bodyPos.z < mCenter.z - mSize.z ||
			bodyPos.z > mCenter.z + mSize.z)
		{
			if (mParent)
			{
				mParent->MoveCollisionObject(mCollisionObjects[i]);
				mCollisionObjects.erase(mCollisionObjects.begin() + i);
				i--;
			}
			else
			{
				//TODO: Inform PhysicsManager
				mCollisionObjects.erase(mCollisionObjects.begin() + i);
				i--;

			}
		}
	}

	if (mChildren[0])
	{
		for (auto& i : mChildren)
		{
			i->UpdateTree();
		}

		auto deleteChildren = true;

		for (auto& i : mChildren)
		{
			if (i->HasChildren() || i->NumOfRigidBodies() > 0)
			{
				deleteChildren = false;
				break;
			}
		}

		if (deleteChildren)
		{
			for (auto& i : mChildren)
			{
				i = nullptr;
			}
		}
	}
}

void Octree::MoveCollisionObject(CollisionObject * pCollisionObject)
{
	const auto bodyPos = pCollisionObject->GetCurrentPosition();

	if (bodyPos.x < mCenter.x - mSize.x ||
		bodyPos.x > mCenter.x + mSize.x ||
		bodyPos.y < mCenter.y - mSize.y ||
		bodyPos.y > mCenter.y + mSize.y ||
		bodyPos.z < mCenter.z - mSize.z ||
		bodyPos.z > mCenter.z + mSize.z)
	{
		if (mParent)
		{
			mParent->MoveCollisionObject(pCollisionObject);
		}
		else
		{
			//TODO: Inform Physics Manager
			//delete pRigidBody;
		}
	}
	else
	{
		if (mSize.x > 0.03 &&
			mSize.y > 0.03 &&
			mSize.z > 0.03)
		{
			if (mChildren[0])
			{
				for (auto& i : mChildren)
				{
					if (i->AddCollisionObject(pCollisionObject))
					{
						break;
					}
				}
			}
			else
			{
				const auto childSize = mSize / 2.0f;
				glm::vec3 centers[8] =
				{
					mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * 1.0f, childSize.z * 1.0f),
					mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * 1.0f, childSize.z * -1.0f),
					mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * -1.0f, childSize.z * 1.0f),
					mCenter + glm::vec3(childSize.x * 1.0f, childSize.y * -1.0f, childSize.z * -1.0f),
					mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * 1.0f, childSize.z * 1.0f),
					mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * 1.0f, childSize.z * -1.0f),
					mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * -1.0f, childSize.z * 1.0f),
					mCenter + glm::vec3(childSize.x * -1.0f, childSize.y * -1.0f, childSize.z * -1.0f)
				};


				auto found = false;
				for (auto i = 0; i < 8; i++)
				{
					mChildren[i] = std::make_unique<Octree>(centers[i], childSize, this);
					if (!found && mChildren[i]->AddCollisionObject(pCollisionObject))
					{
						found = true;
					}
				}

				for (auto& i : mChildren)
				{
					i->GetNeighbours();
				}
			}
		}
		else
		{
			mCollisionObjects.push_back(pCollisionObject);
		}
	}
}

void Octree::GetNeighbours()
{
	auto grandParent = mParent;

	while (grandParent->mParent)
	{
		grandParent = grandParent->mParent;
	}

	grandParent->FindNeighbour(mCenter, mSize, mNeighbours, this);
}

void Octree::FindNeighbour(const glm::vec3 & pCenter, const glm::vec3 & pSize, std::vector<Octree*>& pNeighbours, Octree* pNeighbour)
{
	if (this == pNeighbour)
	{
		return;
	}

	if (mSize.x > pSize.x)
	{
		for (auto i = 0; i < 8 && mChildren[i]; i++)
		{
			mChildren[i]->FindNeighbour(pCenter, pSize, pNeighbours, pNeighbour);
		}
	}
	else if (mSize.x == pSize.x)
	{
		if (mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 2, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 0, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 0, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * 0, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * -2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * -2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * 2, pSize.y * -2, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * 2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * 2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * 2, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * 0, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * 0, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * -2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * -2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * 0, pSize.y * -2, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 2, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 0, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 0, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * 0, pSize.z * -2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * -2, pSize.z * 2) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * -2, pSize.z * 0) ||
			mCenter == pCenter + glm::vec3(pSize.x * -2, pSize.y * -2, pSize.z * -2))
		{
			if (std::find(pNeighbours.begin(), pNeighbours.end(), this) == pNeighbours.end())
			{
				pNeighbours.push_back(this);
			}

			if (std::find(mNeighbours.begin(), mNeighbours.end(), pNeighbour) == mNeighbours.end()) {
				mNeighbours.push_back(pNeighbour);
			}
		}
	}
}

void Octree::DeleteNeighbour(Octree* pNeighbour)
{
	const auto i = std::find(mNeighbours.begin(), mNeighbours.end(), pNeighbour);

	if (i != mNeighbours.end())
	{
		mNeighbours.erase(i);
	}
}


void Octree::GetPossibleCollisions(std::vector<PossibleCollision>& pPossibleCollisions)
{
	if (mCollisionObjects.empty())
	{
		if (mChildren[0])
		{
			for (auto& i : mChildren)
			{
				i->GetPossibleCollisions(pPossibleCollisions);
			}
		}
	}
	else
	{
		for (auto i = 0u; i < mCollisionObjects.size(); i++)
		{
			for (auto j = i + 1u; j < mCollisionObjects.size(); j++)
			{
				pPossibleCollisions.emplace_back(PossibleCollision{ mCollisionObjects[i], mCollisionObjects[j] });
			}
		}

		mChecked = true;

		for (auto& rigidBody : mCollisionObjects)
		{
			for (auto& neighbour : mNeighbours)
			{
				if (!neighbour->mChecked)
				{
					for (auto& neighbourRigidBody : neighbour->mCollisionObjects)
					{
						pPossibleCollisions.emplace_back(PossibleCollision{ rigidBody, neighbourRigidBody });
					}
				}
			}
		}
	}
}

void Octree::Reset()
{
	if (mChildren[0])
	{
		for (auto& child : mChildren)
		{
			child->Reset();
			child.reset(nullptr);
		}
	}
}