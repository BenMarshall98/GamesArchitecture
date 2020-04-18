#pragma once
#include "CollisionObject.h"

class SphereObject;

class PlaneObject final : public CollisionObject
{
	friend SphereObject;

	glm::vec3 mNormal;

public:
	PlaneObject(Entity * pParent, const glm::vec3 & pPosition, const glm::vec3 & pNormal,
		const std::function<void(CollisionObject*, CollisionObject*)> & pFunction = [](CollisionObject*, CollisionObject*) {});
	~PlaneObject() = default;

	PlaneObject(const PlaneObject &) = delete;
	PlaneObject(PlaneObject&&) = delete;
	PlaneObject & operator= (const PlaneObject &) = delete;
	PlaneObject & operator= (PlaneObject&&) = delete;

	bool Collision(CollisionObject* pCollisionObject, CollisionData & pData) override;
	bool CollisionSphere(SphereObject* pSphereObject, CollisionData & pData) override;
	bool CollisionPlane(PlaneObject* pPlaneObject, CollisionData & pData) override;
};

