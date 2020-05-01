#include "RenderSystem.h"


#include "CameraManager.h"
#include "ConstantBufferLoader.h"
#include "PositionComponent.h"
#include "RenderComponent.h"

#include "glm/gtc/matrix_transform.hpp"

RenderSystem::RenderSystem() : System({ComponentType::POSITION, ComponentType::RENDER}),
	mModelBuffer(std::move(ConstantBufferLoader<ModelMatrix>::CreateConstantBuffer(0))),
	mViewBuffer(std::move(ConstantBufferLoader<ViewProjectionMatrix>::CreateConstantBuffer(1)))
{
	mModelBuffer->Load();
	mViewBuffer->Load();
}

void RenderSystem::Action(const float pDeltaTime)
{
	System::Action(pDeltaTime);

	const auto cameraManager = CameraManager::Instance();

	ViewProjectionMatrix vpMat;
	vpMat.mView = cameraManager->GetViewMatrix();
	vpMat.mProjection = cameraManager->GetPerspectiveMatrix();

	mViewBuffer->UpdateBuffer(vpMat);

	for (auto & entity : mEntities)
	{
		const auto renderComponent = std::dynamic_pointer_cast<RenderComponent>(entity->GetComponentByType(ComponentType::RENDER));
		const auto positionComponent = std::dynamic_pointer_cast<PositionComponent>(entity->GetComponentByType(ComponentType::POSITION));

		const auto position = positionComponent->GetRenderPosition();
		const auto scale = positionComponent->GetScale();

		const auto model = renderComponent->GetModel();
		const auto shader = renderComponent->GetShader();
		const auto texture = renderComponent->GetTexture();

		ModelMatrix modelMat;

		modelMat.mModel = glm::translate(glm::mat4(1.0f), position);
		modelMat.mModel = glm::scale(modelMat.mModel, scale);

		mModelBuffer->UpdateBuffer(modelMat);

		//TODO: Include Texture
		
		shader->UseProgram();
		model->Render();
	}
}