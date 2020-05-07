#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FragmentShader.h"
#include "ModelInstanced.h"
#include "PlaybackSystem.h"
#include "Scene.h"
#include "VertexShader.h"
#include "UserEntity.h"

enum class ProjectileType
{
	SMALL,
	LARGE,
	GRENADE
};

class PyramidScene final : public Scene
{
	int mCurrentSizePyramid = 3;
	int mNextSizePyramid = 3;
	bool mMainCamera = false;

	ProjectileType mProjectile = ProjectileType::SMALL;
	bool mReset = false;

	std::shared_ptr<PlaybackSystem> mPlaybackSystem;
	
	void Reset();

public:
	PyramidScene() = default;
	~PyramidScene() = default;

	PyramidScene(const PyramidScene&) = delete;
	PyramidScene(PyramidScene&&) = delete;
	PyramidScene& operator= (const PyramidScene&) = delete;
	PyramidScene& operator= (PyramidScene&&) = delete;

	void Load() override;
	void Unload() override;
	void Render() override;
	void Update(float pDeltaTime) override;
	void Swap() override;
};