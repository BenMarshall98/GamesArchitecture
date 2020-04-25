#include "DirectXRenderManager.h"

#ifdef DX_11

#include "DirectXFragmentShader.h"
#include "DirectXModel.h"
#include "DirectXShader.h"
#include "DirectXTexture.h"
#include "DirectXVertexShader.h"

std::shared_ptr<Model> DirectXRenderManager::CreateModel(const std::string& pModel)
{
	return std::make_shared<DirectXModel>(pModel);
}

std::shared_ptr<Texture> DirectXRenderManager::CreateTexture(const std::string& pTexture)
{
	return std::make_shared<DirectXTexture>(pTexture);
}

std::shared_ptr<VertexShader> DirectXRenderManager::CreateVertexShader(const std::string& pVertexShader)
{
	return std::make_shared<DirectXVertexShader>(pVertexShader);
}

std::shared_ptr<FragmentShader> DirectXRenderManager::CreateFragmentShader(const std::string& pFragmentShader)
{
	return std::make_shared<DirectXFragmentShader>(pFragmentShader);
}

std::shared_ptr<Shader> DirectXRenderManager::CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader)
{
	return std::make_shared<DirectXShader>(pVertexShader, pFragmentShader);
}

#endif