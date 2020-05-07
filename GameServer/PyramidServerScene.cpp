#include "PyramidServerScene.h"

#include "../GameEngine/EntityManager.h"
#include "../GameEngine/Octree.h"
#include "../GameEngine/PhysicsManager.h"
#include "../GameEngine/PhysicsSystem.h"
#include "../GameEngine/SystemManager.h"
#include "PlaneServerEntity.h"
#include "PyramidShapeServerEntity.h"

void PyramidServerScene::Load()
{
	auto octree = std::make_unique<Octree>(glm::vec3(0.0f), glm::vec3(1.0f));
	PhysicsManager::Instance()->SetPhysicsTree(std::move(octree));

	auto systemManager = SystemManager::Instance();

	auto physicsSystem = std::make_unique<PhysicsSystem>();
	systemManager->AddUpdateSystem(std::move(physicsSystem));

	Reset();
}

void PyramidServerScene::Render()
{
	//Do Nothing
}

void PyramidServerScene::Update(const float pDeltaTime)
{
	EntityManager::Instance()->Update(pDeltaTime);
}

void PyramidServerScene::Unload()
{
}

void PyramidServerScene::Reset()
{
	mCurrentSizePyramid = mNextSizePyramid;

	auto entityManager = EntityManager::Instance();

	entityManager->Reset();

	PhysicsManager::Instance()->Reset();
	
	entityManager->AddEntity(std::make_shared<PlaneServerEntity>());

	const auto offset = 1.0f / sqrt(2.0f) * 0.02f;

	auto mass = false;

	for (auto i = mCurrentSizePyramid; i >= 1; i--)
	{
		const auto y = static_cast<float>(mCurrentSizePyramid - i) * offset + 0.01f;

		for (auto j = 0; j < i; j++)
		{
			for (auto k = 0; k < i; k++)
			{
				const auto x = j * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;
				const auto z = k * 0.02f - static_cast<float>(i) * 0.02f / 2.0f;

				entityManager->AddEntity(std::make_shared<PyramidShapeServerEntity>(glm::vec3(x, y, z), mass));
			}
		}

		mass = true;
	}
}

void PyramidServerScene::Swap()
{
	//TODO

	EntityManager::Instance()->Swap();
}
