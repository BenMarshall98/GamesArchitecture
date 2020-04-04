#pragma once

#include <string>

#include "FragmentShader.h"
#include "VertexShader.h"

class Shader final
{
	std::string mVertexShaderFile;
	std::string mFragmentShaderFile;

	std::shared_ptr<VertexShader> mVertexShader;
	std::shared_ptr<FragmentShader> mFragmentShader;

public:
	Shader(const std::string & pVertexShaderFile, const std::string & pFragmentShaderFile) : mVertexShaderFile(pVertexShaderFile), mFragmentShaderFile(pFragmentShaderFile) {}
	~Shader() = default;

	bool Load();
	void Reset() const;
	void UseProgram();
};

