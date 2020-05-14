#pragma once

#include <glm/mat4x4.hpp>
#include <string>
#include <vector>

#include "Model.h"

class ModelInstanced : public Model
{
protected:
	unsigned int mIndicesSize = 0u;

public:
	explicit ModelInstanced(const std::string & pModelFile);
	virtual ~ModelInstanced() = default;

	ModelInstanced(const ModelInstanced&) = delete;
	ModelInstanced(ModelInstanced &&) = delete;
	ModelInstanced & operator= (const ModelInstanced &) = delete;
	ModelInstanced & operator= (ModelInstanced &&) = delete;

	bool Load() override = 0;
	virtual void Render(const std::vector<glm::mat4> & pBuffer) = 0;
	void Render() override {};
};
