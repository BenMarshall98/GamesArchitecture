#pragma once

#include "glm/glm.hpp"
#include <string>

struct VertexData
{
	glm::vec3 mVertex;
	glm::vec2 mTexCoord;
	glm::vec3 mNormal;
};

class Model
{
protected:
	std::string mModelFile;
	unsigned int mIndicesSize = 0u;

public:
	explicit Model(const std::string & pModelFile);
	virtual ~Model() = default;

	Model(const Model&) = delete;
	Model(Model &&) = delete;
	Model & operator= (const Model &) = delete;
	Model & operator= (Model &&) = delete;

	virtual bool Load() = 0;
	virtual void Render() = 0;
};
