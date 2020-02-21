#pragma once

#include "Model.h"
#include <string>
#include <memory>
#include "ModelInstanced.h"

class ModelLoader
{
public:
	static void loadModelFromFile(const std::string & pModelFile, std::shared_ptr<ModelInstanced> & pModel);
};
