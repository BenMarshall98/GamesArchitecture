#include "RenderComponent.h"

RenderComponent::RenderComponent(const std::shared_ptr<Shader>& pShader, const std::shared_ptr<Model>& pModel,
	const std::shared_ptr<Texture>& pTexture) : Component(ComponentType::RENDER), mShader(pShader),
	mModel(pModel), mTexture(pTexture)
{
}

void RenderComponent::Swap()
{
	//Do Nothing	
}