#include "CollisionObject.h"

CollisionObject::CollisionObject(Entity* pParent, const glm::vec3& pPosition, const glm::vec3& pVelocity,
	float pMass, const std::function<void(CollisionObject*, CollisionObject*)>& pFunction) :
	mParent(pParent), mCurrentPosition(pPosition), mLastPosition(pPosition), mCurrentVelocity(pVelocity),
	mLastVelocity(pVelocity), mMass(pMass), mFunction(pFunction)
{
}