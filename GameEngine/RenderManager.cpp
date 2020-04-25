#include "RenderManager.h"

#include "OpenGLRenderManager.h"
#include "DirectXRenderManager.h"

RenderManager* RenderManager::Instance()
{
	if (!mInstance)
	{
#ifdef GL_430
		mInstance = new OpenGLRenderManager();
#elif DX_11
		mInstance = new DirectXRenderManager();
#endif
	}
	
	return mInstance;
}
