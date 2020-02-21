#include "Win32Window.h"
#include "Dx11Render.h"
#include <DirectXColors.h>
#include <memory>

#include "ModelLoader.h"
#include "Model.h"
#include "VertexShader.h"
#include "FragmentShader.h"

int WINAPI wWinMain(const HINSTANCE pHInstance, HINSTANCE, LPWSTR, const int pCmdShow)
{
	const auto window = Win32Window::instance(pHInstance, pCmdShow);
	window->run();
	const auto render = Dx11Render::instance();

	auto model = std::make_shared<Model>();
	ModelLoader::loadModelFromFile("Assets/Models/sphere.obj", model);

	auto vertexShader = std::make_unique<VertexShader>(L"SimpleVertexProgram.hlsl");
	auto fragmentShader = std::make_unique<FragmentShader>(L"SimpleFragmentProgram.hlsl");

	auto result = vertexShader->Load();
	result = fragmentShader->Load();

	while (window->windowEvents())
	{
		render->clearRenderTargetView(DirectX::Colors::CornflowerBlue);

		vertexShader->UseProgram();
		fragmentShader->UseProgram();
		model->render();

		render->present();
	}

	delete render;
	delete window;

	return 0;
}