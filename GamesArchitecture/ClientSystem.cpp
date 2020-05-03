#include "ClientSystem.h"

#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "ClientNetworkingManager.h"

ClientSystem::ClientSystem(PyramidScene* pScene) :
	System({ComponentType::PHYSICS, ComponentType::POSITION}), mScene(pScene)
{
}

void ClientSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	//TODO: Networking Messages
}