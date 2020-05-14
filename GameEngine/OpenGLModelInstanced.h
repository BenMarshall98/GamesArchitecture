#pragma once

#ifdef GL_430

#include "ModelInstanced.h"

class OpenGLModelInstanced final : public ModelInstanced
{
	unsigned int mIndexSize;
	unsigned int VAO, EBO, VBO, VIO;
	
public:
	explicit OpenGLModelInstanced(const std::string & pModelFile);
	~OpenGLModelInstanced() = default;

	OpenGLModelInstanced(const OpenGLModelInstanced&) = delete;
	OpenGLModelInstanced(OpenGLModelInstanced &&) = delete;
	OpenGLModelInstanced & operator= (const OpenGLModelInstanced &) = delete;
	OpenGLModelInstanced & operator= (OpenGLModelInstanced &&) = delete;

	bool Load() override;
	void Render(const std::vector<glm::mat4>& pBuffer) override;
};

#endif