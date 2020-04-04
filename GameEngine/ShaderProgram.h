#pragma once

#include <string>
#include <d3d11.h>

class ShaderProgram
{
	std::string mFilename;

public:
	ShaderProgram(const std::string & pFilename) : mFilename(pFilename) {}
	virtual ~ShaderProgram() = default;

	virtual bool Load() = 0;
	virtual void Reset() = 0;
	virtual void UseProgram() = 0;

	HRESULT CompileShader(const char * const pTarget, ID3DBlob** const pShaderBlob);
};

