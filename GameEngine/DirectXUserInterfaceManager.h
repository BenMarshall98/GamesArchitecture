#pragma once

#include "UserInterfaceManager.h"

#ifdef DX_11

class DirectXUserInterfaceManager final : public UserInterfaceManager
{
	friend UserInterfaceManager;

	DirectXUserInterfaceManager();

public:
	~DirectXUserInterfaceManager();

	DirectXUserInterfaceManager(const DirectXUserInterfaceManager &) = delete;
	DirectXUserInterfaceManager(DirectXUserInterfaceManager &&) = delete;
	DirectXUserInterfaceManager & operator= (const DirectXUserInterfaceManager &) = delete;
	DirectXUserInterfaceManager & operator= (DirectXUserInterfaceManager &&) = delete;

	void NewFrame() override;
	void Render() override;
};

#endif