#pragma once


#ifdef DX_11

#include <wrl/client.h>
#include <d3d11_1.h>
#include <DirectXColors.h>
#include "Win32Window.h"

#include "RenderManager.h"

class DirectXRenderManager final : public RenderManager
{
	friend RenderManager;

	D3D_DRIVER_TYPE mDriverType = D3D_DRIVER_TYPE_HARDWARE;
	D3D_FEATURE_LEVEL mFeatureLevel = D3D_FEATURE_LEVEL_10_0;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> mSwapChain1;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11Debug> mDebug;

	DirectXRenderManager() = default;

public:
	~DirectXRenderManager() = default;

	DirectXRenderManager(const DirectXRenderManager &) = delete;
	DirectXRenderManager(DirectXRenderManager &&) = delete;
	DirectXRenderManager & operator= (const DirectXRenderManager &) = delete;
	DirectXRenderManager & operator= (DirectXRenderManager &&) = delete;

	bool Load() override;

	std::shared_ptr<Model> CreateModel(const std::string& pModel) override;
	std::shared_ptr<Texture> CreateTexture(const std::string& pTexture) override;
	std::shared_ptr<VertexShader> CreateVertexShader(const std::string& pVertexShader) override;
	std::shared_ptr<FragmentShader> CreateFragmentShader(const std::string& pFragmentShader) override;
	std::shared_ptr<Shader> CreateShader(const std::string& pVertexShader, const std::string& pFragmentShader) override;
	std::shared_ptr<ModelInstanced> CreateInstancedModel(const std::string& pModel) override;

	void ClearRenderTargetView(const DirectX::XMVECTORF32& pColor) const override;

	void Present() const override;

	void GetDevice(Microsoft::WRL::ComPtr<ID3D11Device> & pDevice) const
	{
		pDevice = mDevice;
	}

	void GetDeviceContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext> & pDeviceContext) const
	{
		pDeviceContext = mDeviceContext;
	}
};

#endif