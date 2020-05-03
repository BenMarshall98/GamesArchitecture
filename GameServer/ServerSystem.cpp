#include "ServerSystem.h"

#include "../GameEngine/PositionComponent.h"
#include "../GameEngine/PhysicsComponent.h"
#include "../GameEngine/ServerNetworkingManager.h"

ServerSystem::ServerSystem(PyramidServerScene* pScene) :
	System({ComponentType::PHYSICS, ComponentType::POSITION}), mScene(pScene)
{
}

void ServerSystem::Action(float pDeltaTime)
{
	System::Action(pDeltaTime);

	//TODO: Networking Messages
}