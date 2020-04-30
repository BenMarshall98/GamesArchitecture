#include "CollisionObject.h"

CollisionObject::CollisionObject(Entity* pParent, const glm::vec3& pPosition, const glm::vec3& pVelocity,
	float pMass, const std::function<void(CollisionObject*, CollisionObject*)>& pFunction) :
	mParent(pParent), mCurrentPosition(pPosition), mLastPosition(pPosition), mCurrentVelocity(pVelocity),
	mLastVelocity(pVelocity), mMass(pMass), mFunction(pFunction)
{
	if (mMass == 0)
	{
		mType = RigidBodyType::STATIC;
	}
	else
	{
		mType = RigidBodyType::DYNAMIC;
	}
}

void CollisionObject::Update(const float pDeltaTime)
{
	State state = {
		mCurrentPosition,
		mCurrentVelocity
	};

	Integrate(state, pDeltaTime);

	mCurrentPosition = state.mPosition;
	mCurrentVelocity = state.mVelocity;
}

void CollisionObject::Integrate(State& pState, const float pDeltaTime)
{
	const Derivative initial = {
		glm::vec3(0.0f),
		glm::vec3(0.0f)
	};

	Derivative k1, k2, k3, k4;
	Evaluate(pState, 0.0f, initial, k1);
	Evaluate(pState, pDeltaTime * 0.5f, k1, k2);
	Evaluate(pState, pDeltaTime * 0.5f, k2, k3);
	Evaluate(pState, pDeltaTime, k3, k4);

	const auto dPos = (k1.mVelocity + (k2.mVelocity + k3.mVelocity) * 2.0f + k4.mVelocity) * 1.0f / 6.0f;
	const auto dVel = (k1.mAcceleration + (k2.mAcceleration + k3.mAcceleration) * 2.0f + k4.mAcceleration) * 1.0f / 6.0f;

	pState.mPosition = pState.mPosition + dPos * pDeltaTime;
	pState.mVelocity = pState.mVelocity + dVel * pDeltaTime;
}

void CollisionObject::Evaluate(const State& pInitial, const float pDeltaTime, const Derivative& pDerivative, Derivative & pReturnDerivative)
{
	const State state = {
		pInitial.mPosition + pDerivative.mVelocity * pDeltaTime,
		pInitial.mVelocity + pDerivative.mAcceleration * pDeltaTime
	};

	pReturnDerivative = Derivative();
	pReturnDerivative.mVelocity = state.mVelocity;
	Acceleration(state, pReturnDerivative.mAcceleration);
}

void CollisionObject::Acceleration(const State & pState, glm::vec3 & pAcceleration)
{
	pAcceleration = glm::vec3(0.0f, -0.1f, 0.0f);
}

void CollisionObject::Swap()
{
	mLastPosition = mCurrentPosition;
	mLastVelocity = mCurrentVelocity;
}

void CollisionObject::CollisionResponse(const CollisionData& pData)
{
	if (pData.mTime == 0)
	{
		pData.mObject1->mCurrentPosition = pData.mObject1->mLastPosition;
		pData.mObject1->mCurrentVelocity = pData.mObject1->mLastVelocity;

		pData.mObject2->mCurrentPosition = pData.mObject2->mLastPosition;
		pData.mObject2->mCurrentVelocity = pData.mObject2->mLastVelocity;
	}
}
