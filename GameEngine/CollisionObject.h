#pragma once

#include "glm/glm.hpp"

class PlaneObject;
class SphereObject;

enum class RigidBodyType
{
	DYNAMIC,
	STATIC
};

class CollisionObject
{
	glm::vec3 mLastPosition;
	glm::vec3 mCurrentPosition;
	
	glm::vec3 mLastVelocity;
	glm::vec3 mCurrentVelocity;

	float mMass;

	RigidBodyType pType;

public:
	CollisionObject(const glm::vec3 & pPosition, const glm::vec3 & pVelocity, float pMass = 0.0f);
	~CollisionObject() = default;

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

	bool Collision(CollisionObject * pCollisionObject);
	bool CollisionSphere(SphereObject * pSphereObject);
	bool CollisionPlane(PlaneObject * pPlaneObject);

	void CollisionResponse(CollisionObject * pCollisionObject);
	void CollisionResponseSphere(SphereObject * pSphereObject);
	void CollisionResponsePlane(PlaneObject * pPlaneObject);
};

