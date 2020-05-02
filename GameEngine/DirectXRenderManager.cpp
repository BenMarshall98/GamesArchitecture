#include "DirectXRenderManager.h"

#ifdef DX_11

#include "DirectXFragmentShader.h"
#include "DirectXModel.h"
#include "DirectXShader.h"
#include "DirectXTexture.h"
#include "DirectXVertexShader.h"
#include <vector>

bool DirectXRenderManager::Load()
{
	const auto window = Win32Window::Instance();

	std::vector<D3D_FEATURE_LEVEL> featureLevels;
	featureLevels.emplace_back(D3D_FEATURE_LEVEL_11_1);
	featureLevels.emplace_back(D3D_FEATURE_LEVEL_11_0);
	featureLevels.emplace_back(D3D_FEATURE_LEVEL_10_1);
	featureLevels.emplace_back(D3D_FEATURE_LEVEL_10_0);

	const UINT flags = D3D11_CREATE_DEVICE_DEBUG;

	auto result = D3D11CreateDevice(nullptr, mDriverType, nullptr, flags, featureLevels.data(), 4, D3D11_SDK_VERSION, &mDevice, &mFeatureLevel, &mDeviceContext);

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	result = mDevice.As(&dxgiDevice);

	if (FAILED(result))
	{
		return false;
	}

	result = mDevice.As(&mDebug);

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;
	result = dxgiDevice->GetAdapter(&dxgiAdapter);

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory1 = nullptr;
	result = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory1));

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;
	result = dxgiFactory1.As(&dxgiFactory2);

	if (FAILED(result))
	{
		return false;
	}

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof swapChainDesc);

	swapChainDesc.Width = window->GetWidth();
	swapChainDesc.Height = window->GetHeight();
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;

	dxgiFactory2->CreateSwapChainForHwnd(mDevice.Get(), window->GetHwnd(), &swapChainDesc, nullptr, nullptr, &mSwapChain1);

	result = mSwapChain1->QueryInterface(IID_PPV_ARGS(&mSwapChain));

	if (FAILED(result))
	{
		return false;
	}

	//Create Color Backbuffer
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
	result = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	if (FAILED(result))
	{
		return false;
	}

	result = mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mRenderTargetView.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	//Create Depth / Stencil BackBuffer
	D3D11_TEXTURE2D_DESC depthTextureDesc;
	depthTextureDesc.Width = window->GetWidth();
	depthTextureDesc.Height = window->GetHeight();
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.MiscFlags = 0;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
	result = mDevice->CreateTexture2D(&depthTextureDesc, nullptr, depthStencil.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC depthStateDesc;
	depthStateDesc.DepthEnable = true;
	depthStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStateDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStateDesc.StencilEnable = false;
	depthStateDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthStateDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	depthStateDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStateDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStateDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStateDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

	depthStateDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStateDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	depthStateDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStateDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthState = nullptr;

	result = mDevice->CreateDepthStencilState(&depthStateDesc, depthState.GetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	mDeviceContext->OMSetDepthStencilState(depthState.Get(), 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;
	depthViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Flags = 0;
	depthViewDesc.Texture2D.MipSlice = 0;

	result = mDevice->CreateDepthStencilView(depthStencil.Get(), &depthViewDesc, mDepthView.GetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	mDeviceContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthView.Get());

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(window->GetWidth());
	viewport.Height = static_cast<float>(window->GetHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	mDeviceContext->RSSetViewports(1, &viewport);

	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.ScissorEnable = false;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.DepthClipEnable = true;
	rasterizerDesc.MultisampleEnable = false;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.AntialiasedLineEnable = true;
	rasterizerDesc.FrontCounterClockwise = true;

	result = mDevice->CreateRasterizerState(&rasterizerDesc, mRasterizerState.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	mDeviceContext->RSSetState(mRasterizerState.Get());

	return true;
}

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
	return std::make_shared<DirectXVertexShader>(pVertexShader + ".hlsl");
}

std::shared_ptr<FragmentShader> DirectXRenderManager::CreateFragmentShader(const std::string& pFragmentShader)
{
	return std::make_shared<DirectXFragmentShader>(pFragmentShader + ".hlsl");
}

std::shared_ptr<Shader> DirectXRenderManager::CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader)
{
	return std::make_shared<DirectXShader>(pVertexShader, pFragmentShader);
}

void DirectXRenderManager::ClearRenderTargetView(const DirectX::XMVECTORF32& pColor) const
{
	mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), pColor);
	mDeviceContext->ClearDepthStencilView(mDepthView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
}

void DirectXRenderManager::Present() const
{
	mSwapChain->Present(0, 0);
}

#endif
