#include "OpenGLRenderManager.h"

#ifdef GL_430

#include "OpenGLFragmentShader.h"
#include "OpenGLModel.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexShader.h"

std::shared_ptr<Model> OpenGLRenderManager::CreateModel(const std::string& pModel)
{
	return std::make_shared<OpenGLModel>(pModel);
}

std::shared_ptr<Texture> OpenGLRenderManager::CreateTexture(const std::string& pTexture)
{
	return std::make_shared<OpenGLTexture>(pTexture);
}

std::shared_ptr<VertexShader> OpenGLRenderManager::CreateVertexShader(const std::string& pVertexShader)
{
	return std::make_shared<OpenGLVertexShader>(pVertexShader);
}

std::shared_ptr<FragmentShader> OpenGLRenderManager::CreateFragmentShader(const std::string& pFragmentShader)
{
	return std::make_shared<OpenGLFragmentShader>(pFragmentShader);
}

std::shared_ptr<Shader> OpenGLRenderManager::CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader)
{
	return std::make_shared<OpenGLShader>(pVertexShader, pFragmentShader);
}

#endif