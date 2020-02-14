#pragma once

#include "Model.h"
#include <string>
#include <memory>

class ModelLoader
{
public:
	static void loadModelFromFile(const std::string & pModelFile, std::shared_ptr<Model> & pModel);
};