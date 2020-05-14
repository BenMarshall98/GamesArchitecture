#include "LightingManager.h"

#include "ConstantBufferLoader.h"

LightingManager * LightingManager::mInstance = nullptr;

LightingManager::LightingManager() :
	mPointLightBuffer(std::move(ConstantBufferLoader<PointLightBuffer>::CreateConstantBuffer(2, 2)))
{
	mPointLightBuffer->Load();
}

void LightingManager::UseLights()
{
	PointLightBuffer plBuffer;
	plBuffer.mPosition = mPointLight.mPosition;
	plBuffer.mLightColour = mPointLight.mLightColour;

	mPointLightBuffer->UpdateBuffer(plBuffer);
}
