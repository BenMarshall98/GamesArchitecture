#pragma once

#include <functional>


#include "Entity.h"
#include "glm/glm.hpp"

class PlaneObject;
class SphereObject;
class CollisionObject;

struct CollisionData
{
	CollisionObject * mObject1;
	CollisionObject * mObject2;
	glm::vec3 mCollisionNormal;
	float mTime;
	float mDepth;
};

struct State
{
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
};

struct Derivative
{
	glm::vec3 mVelocity;
	glm::vec3 mAcceleration;
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

	static void Integrate(State & pState, const float pDeltaTime);
	static void Evaluate(const State & pInitial, const float pDeltaTime, const Derivative & pDerivative, Derivative & pReturnDerivative);
	static void Acceleration(const State & pState, glm::vec3 & pAcceleration);

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

	RigidBodyType GetType() const
	{
		return mType;
	}
	
	glm::vec3 GetLastVelocity() const
	{
		return mLastVelocity;
	}
	
	glm::vec3 GetLastPosition() const
	{
		return mLastPosition;
	}
	
	glm::vec3 GetCurrentVelocity() const
	{
		return mCurrentVelocity;
	}
	
	glm::vec3 GetCurrentPosition() const
	{
		return mCurrentPosition;
	}

	void Update(float pDeltaTime);
	void Swap();

	virtual bool Collision(CollisionObject * pCollisionObject, CollisionData & pData) = 0;
	virtual bool CollisionSphere(SphereObject * pSphereObject, CollisionData & pData) = 0;
	virtual bool CollisionPlane(PlaneObject * pPlaneObject, CollisionData & pData) = 0;

	static void CollisionResponse(const CollisionData & pData, float pDeltaTime);
};

