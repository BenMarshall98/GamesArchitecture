#pragma once

#include <glm/vec3.hpp>
#include <memory>


#include "ConstantBuffer.h"

struct PointLight
{
	glm::vec3 mPosition;
	glm::vec3 mLightColour;
};

struct PointLightBuffer
{
	glm::vec3 mPosition;
	float mPadding1;
	glm::vec3 mLightColour;
	float mPadding2;
};

class LightingManager
{
	PointLight mPointLight;
	std::unique_ptr<ConstantBuffer<PointLightBuffer>> mPointLightBuffer;

	LightingManager();
	static LightingManager * mInstance;

public:
	static LightingManager * Instance()
	{
		if (!mInstance)
		{
			mInstance = new LightingManager();
		}

		return mInstance;
	}

	~LightingManager() = default;

	LightingManager(const LightingManager&) = delete;
	LightingManager(LightingManager&&) = delete;
	LightingManager& operator= (const LightingManager&) = delete;
	LightingManager& operator= (LightingManager&&) = delete;

	void SetPointLight(const PointLight & pPointLight)
	{
		mPointLight = pPointLight;
	}
	
	void UseLights();
};

