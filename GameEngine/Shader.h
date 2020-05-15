#pragma once

#include <string>

#include "FragmentShader.h"
#include "VertexShader.h"

class Shader
{
protected:
	std::shared_ptr<VertexShader> mVertexShader;
	std::shared_ptr<FragmentShader> mFragmentShader;
	
	std::string mVertexShaderFile;
	std::string mFragmentShaderFile;

public:
	Shader(const std::string & pVertexShaderFile, const std::string & pFragmentShaderFile) : mVertexShaderFile(pVertexShaderFile), mFragmentShaderFile(pFragmentShaderFile) {}
	virtual ~Shader() = default;

	virtual bool Load();
	virtual void Reset() const = 0;
	virtual void UseProgram() = 0;

	std::string GetVertexShaderFilename() const
	{
		return mVertexShaderFile;
	}

	std::string GetFragmentShaderFilename() const
	{
		return mFragmentShaderFile;
	}
};

