#pragma once

#include "ShaderProgram.h"

class VertexShader : public ShaderProgram
{
public:
	explicit VertexShader(const std::string & pFilename) : ShaderProgram(pFilename) {};
	~VertexShader() = default;

	VertexShader(const VertexShader &) = delete;
	VertexShader(VertexShader &&) = delete;
	VertexShader & operator= (const VertexShader &) = delete;
	VertexShader & operator= (VertexShader &&) = delete;
};

