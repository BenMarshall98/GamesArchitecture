#pragma once

#ifdef DX_11

#include <d3d11.h>
#include <wrl/client.h>
#include "ModelInstanced.h"

class DirectXModelInstanced final : public ModelInstanced
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> mMeshBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mModelBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndicesBuffer = nullptr;
public:
	explicit DirectXModelInstanced(const std::string & pModelFile);
	~DirectXModelInstanced() = default;

	DirectXModelInstanced(const DirectXModelInstanced&) = delete;
	DirectXModelInstanced(DirectXModelInstanced &&) = delete;
	DirectXModelInstanced & operator= (const DirectXModelInstanced &) = delete;
	DirectXModelInstanced & operator= (DirectXModelInstanced &&) = delete;

	bool Load() override;
	void Render(const std::vector<glm::mat4> & pBuffer) override;
};

#endif