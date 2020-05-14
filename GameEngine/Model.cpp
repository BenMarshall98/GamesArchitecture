#include "Model.h"

Model * Model::mLastModel = nullptr;

Model::Model(const std::string & pModelFile) : mModelFile(pModelFile)
{
}