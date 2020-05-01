#pragma once

#ifdef DX_11

#include <wrl/client.h>
#include <d3d11.h>
#include "ConstantBuffer.h"

template <class T>
class DirectXConstantBuffer final : public ConstantBuffer<T>
{
	using ConstantBuffer<T>::mVSSlot;
	using ConstantBuffer<T>::mPSSlot;
	
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;

public:
	DirectXConstantBuffer(int pVsSlot = -1, int pPsSlot = -1);
	~DirectXConstantBuffer() = default;

	DirectXConstantBuffer(const DirectXConstantBuffer &) = delete;
	DirectXConstantBuffer(DirectXConstantBuffer &&) = delete;
	DirectXConstantBuffer & operator= (const DirectXConstantBuffer &) = delete;
	DirectXConstantBuffer & operator= (DirectXConstantBuffer &&) = delete;

	bool Load() override;
	void Reset() override;
	void UpdateBuffer(const T & pData) override;
};

#include "DirectXRenderManager.h"

template <class T>
DirectXConstantBuffer<T>::DirectXConstantBuffer(int pVsSlot, int pPsSlot) : ConstantBuffer<T>(pVsSlot, pPsSlot)
{
}

template <class T>
bool DirectXConstantBuffer<T>::Load()
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof bd);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(T);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;


	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	const auto result = device->CreateBuffer(&bd, nullptr, mConstantBuffer.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

template <class T>
void DirectXConstantBuffer<T>::Reset()
{
	mConstantBuffer.Reset();
}

template <class T>
void DirectXConstantBuffer<T>::UpdateBuffer(const T & pData)
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	deviceContext->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &pData, 0, 0);

	if (mVSSlot >= 0)
	{
		deviceContext->VSSetConstantBuffers(mVSSlot, 1, mConstantBuffer.GetAddressOf());
	}

	if (mPSSlot >= 0)
	{
		deviceContext->PSSetConstantBuffers(mPSSlot, 1, mConstantBuffer.GetAddressOf());
	}
}

#endif