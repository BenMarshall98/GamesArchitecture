#pragma once

#include <string>
#include <d3d11.h>

class ShaderProgram
{
	std::wstring mFilename;

public:
	ShaderProgram(const std::wstring & pFilename) : mFilename(pFilename) {};
	virtual ~ShaderProgram() {};

	virtual bool Load() = 0;
	virtual void Reset() = 0;
	virtual void UseProgram() = 0;

	HRESULT CompileShader(const char * const pTarget, ID3DBlob** const pShaderBlob);
};

