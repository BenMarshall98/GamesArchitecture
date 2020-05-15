#include "RenderManager.h"


#include "ConstantBufferLoader.h"
#include "OpenGLRenderManager.h"
#include "DirectXRenderManager.h"
#include "ResourceManager.h"

RenderManager * RenderManager::mInstance = nullptr;

RenderManager::RenderManager() : mModelBuffer(std::move(ConstantBufferLoader<ModelMatrix>::CreateConstantBuffer(0)))
{
}

RenderManager* RenderManager::Instance()
{
	if (!mInstance)
	{
#ifdef GL_430
		mInstance = new OpenGLRenderManager();
#elif DX_11
		mInstance = new DirectXRenderManager();
#endif

		if (!mInstance->Load())
		{
			delete mInstance;
			mInstance = nullptr;
		}
	}
	
	return mInstance;
}

void RenderManager::AddRenderSetup(const std::shared_ptr<Model>& pModel, const std::shared_ptr<Shader>& pShader, const glm::mat4 & pModelMatrix)
{
	static auto first = true;
	
	if (first)
	{
		mModelBuffer->Load();
		first = false;
	}
	
	for (auto it = mRenderObjects.begin();; ++it)
	{
		if (it == mRenderObjects.end())
		{
			mRenderObjects.insert(std::pair<RenderSetup *, std::vector<glm::mat4>>(new RenderSetup{ pModel, pShader }, { pModelMatrix }));
			return;
		}
		
		if (pModel == it->first->mModel && pShader == it->first->mShader)
		{
			it->second.push_back(pModelMatrix);
			return;
		}
	}
}

void RenderManager::Render()
{
	for (auto it = mRenderObjects.begin(); it != mRenderObjects.end(); ++it)
	{
		if (it->second.size() < 100)
		{
			it->first->mShader->UseProgram();
			
			for (int i = 0; i < it->second.size(); i++)
			{
				ModelMatrix modelMat;
				modelMat.mModel = it->second[i];
				mModelBuffer->UpdateBuffer(modelMat);
				
				it->first->mModel->Render();
			}
		}
		else
		{
			auto insta = mInstancedModels.find(it->first);

			if (insta == mInstancedModels.end())
			{

				auto shader = ResourceManager::Instance()->LoadShader(std::string(it->first->mShader->GetVertexShaderFilename() + std::string("Instanced")), it->first->mShader->GetFragmentShaderFilename());
				auto renderModel = it->first;

				auto model = CreateInstancedModel(it->first->mModel->GetFilename());
				model->Load();
				mInstancedModels.insert(std::pair<RenderSetup *, std::vector<std::shared_ptr<ModelInstanced>>>(it->first, { model }));
				mInstancedShaders.insert(
					std::pair<RenderSetup *, std::shared_ptr<Shader>>(
						renderModel,
						shader
						)
				);
			}

			insta = mInstancedModels.find(it->first);

			const auto instaShader = mInstancedShaders.find(it->first);

			if (insta != mInstancedModels.end())
			{
				int total = it->second.size() / 1000 + 1;

				while (insta->second.size() < total)
				{
					const auto model = CreateInstancedModel(it->first->mModel->GetFilename());
					model->Load();
					insta->second.push_back(model);
				}

				instaShader->second->UseProgram();

				for (int i = 0; i < insta->second.size(); i++)
				{
					std::vector<glm::mat4> modelMats;
					modelMats.reserve(1000);
					
					for (int j = i * 1000; j < it->second.size() && j < (i + 1) * 1000; j++)
					{
						modelMats.push_back(it->second[j]);
					}

					insta->second[i]->Render(modelMats);
				}
			}
		}
	}

	for (auto it = mRenderObjects.begin(); it != mRenderObjects.end(); ++it)
	{
		it->second.shrink_to_fit();
		it->second.clear();
	}
}