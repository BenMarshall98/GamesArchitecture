#pragma once
#include <DirectXMath.h>
#include <memory>

#include "FragmentShader.h"
#include "ModelInstanced.h"
#include "Scene.h"
#include "VertexShader.h"

struct ViewProjectionMatrix
{
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProjection;
};

class PyramidScene final : public Scene
{
	std::shared_ptr<ModelInstanced> mModel;
	std::shared_ptr<VertexShader> mVertexShader;
	std::shared_ptr<FragmentShader> mFragmentShader;
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