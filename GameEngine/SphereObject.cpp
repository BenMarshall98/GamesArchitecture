#include "SphereObject.h"
#include "PlaneObject.h"

SphereObject::SphereObject(const glm::vec3& pPosition, const glm::vec3& pVelocity, float pMass, float pRadius)
	: CollisionObject(pPosition, pVelocity, pMass), mRadius(pRadius)
{
}

bool SphereObject::Collision(CollisionObject* pCollisionObject, CollisionData & pData)
{
	return pCollisionObject->CollisionSphere(this, pData);
}

bool SphereObject::CollisionSphere(SphereObject* pSphereObject, CollisionData & pData)
{
	const auto dist = pSphereObject->mLastPosition - mLastPosition;
	const auto sphereVelocity0 = mCurrentPosition - mLastPosition;
	const auto sphereVelocity1 = pSphereObject->mCurrentPosition - pSphereObject->mLastPosition;

	const auto sphereVelocity = sphereVelocity1 - sphereVelocity0;
	const auto radius = pSphereObject->mRadius + mRadius;
	const auto c = dot(dist, dist) - radius * radius;

	if (c < 0.0f)
	{
		pData.mTime = 0.0f;
		pData.mCollisionNormal = normalize(dist);
		return true;
	}

	const auto a = dot(sphereVelocity, sphereVelocity);

	if (a < FLT_EPSILON)
	{
		return false;
	}

	const auto b = dot(sphereVelocity, dist);

	if (b >= 0.0f)
	{
		return false;
	}

	const auto d = b * b - a * c;

	if (d < 0.0f)
	{
		return false;
	}

	const auto time = (-b - sqrt(d)) / a;
	
	if (time < 0.0f || time > 1.0f)
	{
		return false;
	}
	
	const auto spherePosition0 = mix(mLastPosition, mCurrentPosition, time);
	const auto spherePosition1 = mix(pSphereObject->mLastPosition, pSphereObject->mCurrentPosition, time);

	pData.mTime = time;
	pData.mCollisionNormal = normalize(spherePosition0 - spherePosition1);
	return true;
}

bool SphereObject::CollisionPlane(PlaneObject* pPlaneObject, CollisionData & pData)
{
	const auto planeDist = dot(pPlaneObject->mNormal, pPlaneObject->mLastPosition);
	const auto sphereDist = dot(pPlaneObject->mNormal, mLastPosition) - planeDist;

	if (abs(sphereDist) <= mRadius)
	{
		pData.mTime = 0.0f;
		pData.mCollisionNormal = pPlaneObject->mNormal;
		return true;
	}

	const auto sphereVelocity = mCurrentPosition - mLastPosition;
	const auto denom = dot(pPlaneObject->mNormal, sphereVelocity);

	if (denom * sphereDist >= 0.0f)
	{
		return false;
	}

	const auto radius = sphereDist > 0.0f ? mRadius : -mRadius;
	const auto time = (radius - sphereDist) / denom;

	if (time < 0.0f || time > 1.0f)
	{
		return false;
	}

	pData.mTime = time;
	pData.mCollisionNormal = pPlaneObject->mNormal;
	return true;
}