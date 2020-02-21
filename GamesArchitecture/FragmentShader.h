#pragma once

#include <wrl/client.h>
#include <d3d11.h>

#include "ShaderProgram.h"

class FragmentShader : public ShaderProgram
{
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;

public:
	FragmentShader(const std::wstring & pFilename) : ShaderProgram(pFilename) {};
	~FragmentShader() { Reset(); };

	bool Load() override;
	void Reset() override;
	void UseProgram() override;
};

