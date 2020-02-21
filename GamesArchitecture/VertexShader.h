#pragma once

#include <wrl/client.h>
#include <d3d11.h>

#include "ShaderProgram.h"

class VertexShader : public ShaderProgram
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

public:
	VertexShader(const std::wstring & pFilename) : ShaderProgram(pFilename) {};
	~VertexShader() { Reset(); };

	bool Load() override;
	void Reset() override;
	void UseProgram() override;
};

