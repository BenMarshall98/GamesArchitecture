#pragma once

#ifdef DX_11

#include <wrl/client.h>
#include <d3d11.h>

#include "FragmentShader.h"

class DirectXFragmentShader final : public FragmentShader
{
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;

public:
	explicit DirectXFragmentShader(const std::string & pFilename) : FragmentShader(pFilename) {};
	~DirectXFragmentShader() = default;

	DirectXFragmentShader(const DirectXFragmentShader &) = delete;
	DirectXFragmentShader(DirectXFragmentShader &&) = delete;
	DirectXFragmentShader & operator= (const DirectXFragmentShader &) = delete;
	DirectXFragmentShader & operator= (DirectXFragmentShader &&) = delete;

	bool Load() override;
	void Reset() override;
	void UseProgram() override;
};

#endif