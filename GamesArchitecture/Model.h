#pragma once

#include <DirectXMath.h>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>

struct VertexData
{
	DirectX::XMFLOAT3 mVertex;
	//DirectX::XMFLOAT2 mTexCoord;
	//DirectX::XMFLOAT3 mNormal;
};

class Model
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMeshBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndicesBuffer = nullptr;

	unsigned int mIndicesSize = 0u;

public:
	Model() = default;
	~Model() = default;

	Model(const Model&) = delete;
	Model(Model &&) = delete;
	Model & operator= (const Model &) = delete;
	Model & operator= (Model &&) = delete;

	bool loadModel(const std::vector<VertexData> & pMesh, const std::vector<unsigned int> & pIndices);

	void render();
};
