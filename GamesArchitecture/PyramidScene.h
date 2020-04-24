#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FragmentShader.h"
#include "ModelInstanced.h"
#include "Scene.h"
#include "VertexShader.h"

class PyramidScene final : public Scene
{
	int mCurrentSizePyramid = 3;
	int mNextSizePyramid = 3;

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
};