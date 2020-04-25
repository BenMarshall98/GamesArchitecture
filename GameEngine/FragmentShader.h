#pragma once

#include "ShaderProgram.h"

class FragmentShader : public ShaderProgram
{
public:
	explicit FragmentShader(const std::string & pFilename) : ShaderProgram(pFilename) {};
	~FragmentShader() = default;

	FragmentShader(const FragmentShader &) = delete;
	FragmentShader(FragmentShader &&) = delete;
	FragmentShader & operator= (const FragmentShader &) = delete;
	FragmentShader & operator= (FragmentShader &&) = delete;
};

