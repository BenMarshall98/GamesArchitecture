#pragma once
#include "CollisionObject.h"

class PlaneObject;

class SphereObject final : public CollisionObject
{
	friend PlaneObject;
	
	float mRadius;
	
public:
	SphereObject(Entity * pParent, const glm::vec3 & pPosition, const glm::vec3 & pVelocity, float pMass, float pRadius,
		const std::function<void(CollisionObject*, CollisionObject*)> & pFunction = [](CollisionObject*, CollisionObject*){});
	~SphereObject() = default;

	SphereObject(const SphereObject &) = delete;
	SphereObject(SphereObject&&) = delete;
	SphereObject & operator= (const SphereObject &) = delete;
	SphereObject & operator= (SphereObject&&) = delete;

	bool Collision(CollisionObject* pCollisionObject, CollisionData & pData) override;
	bool CollisionSphere(SphereObject* pSphereObject, CollisionData & pData) override;
	bool CollisionPlane(PlaneObject* pPlaneObject, CollisionData & pData) override;
};

