#pragma once

#ifdef DX_11

#include <d3d11.h>
#include <wrl/client.h>

#include "Model.h"

class DirectXModel final : public Model
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMeshBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndicesBuffer = nullptr;

public:
	explicit DirectXModel(const std::string & pModelFile) : Model(pModelFile) {}
	~DirectXModel() = default;

	DirectXModel(const DirectXModel&) = delete;
	DirectXModel(DirectXModel &&) = delete;
	DirectXModel & operator= (const DirectXModel &) = delete;
	DirectXModel & operator= (DirectXModel &&) = delete;

	bool Load() override;
	void Render() override;
};

#endif