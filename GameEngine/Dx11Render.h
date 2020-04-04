#pragma once

#include <d3d11_1.h>
#include <DirectXMath.h>
#include <WRL/client.h>
#include "Win32Window.h"

class Dx11Render
{
	static Dx11Render * mInstance;

	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> mSwapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11Debug> mDebug;

	Dx11Render();
	bool loadRender();

public:
	static Dx11Render * instance();

	void clearRenderTargetView(const DirectX::XMVECTORF32 & pColor) const
	{
		mDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), pColor);
		mDeviceContext->ClearDepthStencilView(mDepthView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0.0f);
	}

	void present() const
	{
		mSwapChain->Present(0, 0);
	}

	void getDevice(Microsoft::WRL::ComPtr<ID3D11Device> & pDevice) const
	{
		pDevice = mDevice;
	}

	void getDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> & pDeviceContext) const
	{
		pDeviceContext = mDeviceContext;
	}

	void defaultViewport()
	{
		D3D11_VIEWPORT viewport;
		viewport.Width = static_cast<float>(Win32Window::instance()->getWidth());
		viewport.Height = static_cast<float>(Win32Window::instance()->getHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		mDeviceContext->RSSetViewports(1, &viewport);
	}

	~Dx11Render();
	Dx11Render(const Dx11Render&) = delete;
	Dx11Render(Dx11Render &&) = delete;
	Dx11Render & operator= (const Dx11Render &) = delete;
	Dx11Render & operator= (Dx11Render &&) = delete;
};