#pragma once

#include <functional>


#include "Entity.h"
#include "glm/glm.hpp"

class PlaneObject;
class SphereObject;

struct CollisionData
{
	glm::vec3 mCollisionNormal;
	float mTime;
};

enum class RigidBodyType
{
	DYNAMIC,
	STATIC
};

class CollisionObject
{
protected:
	glm::vec3 mLastPosition;
	glm::vec3 mCurrentPosition;
	
	glm::vec3 mLastVelocity;
	glm::vec3 mCurrentVelocity;

	float mMass;

	RigidBodyType mType;

	std::function<void(CollisionObject*, CollisionObject*)> mFunction;

	Entity * mParent;

public:
	CollisionObject(Entity * pParent, const glm::vec3 & pPosition, const glm::vec3 & pVelocity, float pMass = 0.0f,
		const std::function<void(CollisionObject*, CollisionObject*)> & pFunction = [](CollisionObject*, CollisionObject*){});
	virtual ~CollisionObject() = default;

	CollisionObject(const CollisionObject &) = delete;
	CollisionObject(CollisionObject&&) = delete;
	CollisionObject & operator= (const CollisionObject &) = delete;
	CollisionObject & operator= (CollisionObject&&) = delete;

	void SetVelocity(const glm::vec3 & pVelocity);
	void ApplyImpluse(const glm::vec3 & pImpulse);
	
	glm::vec3 GetVelocity() const;
	glm::vec3 GetPosition() const;

	void Update();
	void Swap();

	virtual bool Collision(CollisionObject * pCollisionObject, CollisionData & pData) = 0;
	virtual bool CollisionSphere(SphereObject * pSphereObject, CollisionData & pData) = 0;
	virtual bool CollisionPlane(PlaneObject * pPlaneObject, CollisionData & pData) = 0;

	void CollisionResponse(CollisionObject * pCollisionObject, const CollisionData & pData);
};

