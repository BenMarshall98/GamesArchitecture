#pragma once

#ifdef DX_11

#include "Shader.h"

class DirectXShader final : public Shader
{
public:
	DirectXShader(const std::string & pVertexShaderFile, const std::string & pFragmentShaderFile);
	~DirectXShader() = default;

	DirectXShader(const DirectXShader &) = delete;
	DirectXShader(DirectXShader &&) = delete;
	DirectXShader & operator= (const DirectXShader &) = delete;
	DirectXShader & operator= (DirectXShader &&) = delete;

	bool Load() override;
	void Reset() const override;
	void UseProgram() override;
};

#endif