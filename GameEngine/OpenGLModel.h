#pragma once

#ifdef GL_430

#include "Model.h"

class OpenGLModel final : public Model
{
	unsigned int mIndexSize;
	unsigned int VAO, EBO, VBO;
	
public:
	OpenGLModel(const std::string & pModelFile) : Model(pModelFile) {}
	~OpenGLModel();

	OpenGLModel(const OpenGLModel &) = delete;
	OpenGLModel(OpenGLModel &&) = delete;
	OpenGLModel & operator= (const OpenGLModel &) = delete;
	OpenGLModel & operator= (OpenGLModel &&) = delete;

	bool Load() override;
	void Render() override;
};

#endif