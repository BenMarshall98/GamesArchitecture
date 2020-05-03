#pragma once

#include "PyramidScene.h"
#include "System.h"

class ClientSystem final : public System
{
	PyramidScene * mScene;
	
public:
	explicit ClientSystem(PyramidScene * pScene);
	~ClientSystem() = default;

	ClientSystem(const ClientSystem &) = delete;
	ClientSystem(ClientSystem&&) = delete;
	ClientSystem & operator= (const ClientSystem &) = delete;
	ClientSystem & operator= (ClientSystem&&) = delete;

	void Action(float pDeltaTime) override;
};