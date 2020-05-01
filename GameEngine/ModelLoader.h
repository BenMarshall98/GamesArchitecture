#pragma once

#include "Model.h"
#include <string>
#include <vector>

#include "ModelInstanced.h"

class ModelLoader
{
public:
	static void LoadModelFromFile(const std::string & pModelFile, std::vector<VertexData> & pMesh, std::vector<unsigned int> & pIndices);
};
