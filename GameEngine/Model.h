#pragma once

#include <DirectXMath.h>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>

struct VertexData
{
	DirectX::XMFLOAT3 mVertex;
	DirectX::XMFLOAT2 mTexCoord;
	DirectX::XMFLOAT3 mNormal;
};

class Model
{
	std::string mModelFile;
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMeshBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndicesBuffer = nullptr;

	unsigned int mIndicesSize = 0u;

public:
	Model(const std::string & pModelFile);
	~Model() = default;

	Model(const Model&) = delete;
	Model(Model &&) = delete;
	Model & operator= (const Model &) = delete;
	Model & operator= (Model &&) = delete;

	bool Load();

	void Render();
};
