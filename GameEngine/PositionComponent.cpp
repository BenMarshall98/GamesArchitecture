#include "PositionComponent.h"

PositionComponent::PositionComponent(const glm::vec3& pPosition, const glm::vec3& pScale) :
	Component(ComponentType::POSITION), mRenderPosition(pPosition), mUpdatePosition(pPosition), mScale(pScale)
{
}

void PositionComponent::Swap()
{
	mRenderPosition = mUpdatePosition;
}