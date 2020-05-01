#pragma once

#ifdef DX_11

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <vector>
#include "Model.h"

class ModelInstanced
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndicesBuffer = nullptr;
	int mIndicesSize;

public:
	ModelInstanced() = default;
	~ModelInstanced() = default;

	bool loadModel(const std::vector<VertexData> & pMesh, const std::vector<unsigned int> & pIndices);
	void render(unsigned int pInstances) const;
};

#endif