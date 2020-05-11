#include "OpenGLRenderManager.h"

#include "Win32Window.h"

#ifdef GL_430

#include "wglext.h"
#include "OpenGL.h"
#include "OpenGLFragmentShader.h"
#include "OpenGLModel.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexShader.h"

#pragma comment(lib, "opengl32.lib")

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
	return std::make_shared<OpenGLVertexShader>(pVertexShader + ".vert");
}

std::shared_ptr<FragmentShader> OpenGLRenderManager::CreateFragmentShader(const std::string& pFragmentShader)
{
	return std::make_shared<OpenGLFragmentShader>(pFragmentShader + ".frag");
}

std::shared_ptr<Shader> OpenGLRenderManager::CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader)
{
	return std::make_shared<OpenGLShader>(pVertexShader, pFragmentShader);
}

bool OpenGLRenderManager::Load()
{
	GLuint PixelFormat;
	HGLRC hRc = NULL;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	hDc = GetDC(Win32Window::Instance()->GetHwnd());

	PixelFormat = ChoosePixelFormat(hDc, &pfd);

	if (PixelFormat == 0)
	{
		return false;
	}

	bool result = SetPixelFormat(hDc, PixelFormat, &pfd);

	if (!result)
	{
		return false;
	}

	HGLRC tempContext = wglCreateContext(hDc);
	wglMakeCurrent(hDc, tempContext);

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 3,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

	auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalEXT(0);

	hRc = wglCreateContextAttribsARB(hDc, 0, attributes);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempContext);
	wglMakeCurrent(hDc, hRc);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void OpenGLRenderManager::ClearRenderTargetView(const DirectX::XMVECTORF32& pColor) const
{
	glClearColor(DirectX::XMVectorGetX(pColor), DirectX::XMVectorGetY(pColor), DirectX::XMVectorGetZ(pColor), DirectX::XMVectorGetW(pColor));
	glClearDepth(1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderManager::Present() const
{
	SwapBuffers(hDc);
}

#endif