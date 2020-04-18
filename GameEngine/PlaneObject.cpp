#include "PlaneObject.h"

#include "SphereObject.h"

PlaneObject::PlaneObject(const glm::vec3& pPosition, const glm::vec3& pNormal) :
	CollisionObject(pPosition, glm::vec3(0.0f), 0.0f), mNormal(pNormal)
{
}

bool PlaneObject::Collision(CollisionObject * pCollisionObject, CollisionData & pData)
{
	return pCollisionObject->CollisionPlane(this, pData);
}

bool PlaneObject::CollisionSphere(SphereObject* pSphereObject, CollisionData & pData)
{
	return pSphereObject->CollisionPlane(this, pData);
}

bool PlaneObject::CollisionPlane(PlaneObject* pPlaneObject, CollisionData & pData)
{
	return false;
}
