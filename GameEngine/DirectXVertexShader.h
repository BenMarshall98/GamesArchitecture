#pragma once

#ifdef DX_11

#include <wrl/client.h>
#include <d3d11.h>

#include "VertexShader.h"

class DirectXVertexShader final : public VertexShader
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

public:
	explicit DirectXVertexShader(const std::string & pFilename) : VertexShader(pFilename) {};
	~DirectXVertexShader() = default;

	DirectXVertexShader(const DirectXVertexShader &) = delete;
	DirectXVertexShader(DirectXVertexShader &&) = delete;
	DirectXVertexShader & operator= (const DirectXVertexShader &) = delete;
	DirectXVertexShader & operator= (DirectXVertexShader &&) = delete;

	bool Load() override;
	void Reset() override;
	void UseProgram() override;
};

#endif