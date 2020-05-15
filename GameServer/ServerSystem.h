#pragma once

#include "PyramidServerScene.h"
#include "../GameEngine/System.h"

class ServerSystem final : public System
{
	PyramidServerScene * mScene;
	int mResetCount = 0;
	bool mResetComplete = true;
	int count = 0;
	
public:
	explicit ServerSystem(PyramidServerScene * pScene);
	~ServerSystem() = default;

	ServerSystem(const ServerSystem &) = delete;
	ServerSystem(ServerSystem&&) = delete;
	ServerSystem & operator= (const ServerSystem &) = delete;
	ServerSystem & operator= (ServerSystem&&) = delete;

	void Action(float pDeltaTime) override;
};