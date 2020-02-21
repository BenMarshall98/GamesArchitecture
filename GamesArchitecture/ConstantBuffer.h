#pragma once

#include <wrl/client.h>
#include "Dx11Render.h"

template <class T>
class ConstantBuffer
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
	int mVSSlot;
	int mPSSlot;

public:
	ConstantBuffer(int pVSSlot = -1, int pPSSlot = -1);

	bool Load();
	void Reset();
	void UpdateBuffer(const T & pData);

	~ConstantBuffer();
};

template <class T>
ConstantBuffer<T>::ConstantBuffer(int pVSSlot, int pPSSlot) : mVSSlot(pVSSlot), mPSSlot(pPSSlot)
{
}

template<class T>
ConstantBuffer<T>::~ConstantBuffer()
{
	Reset();
}

template<class T>
bool ConstantBuffer<T>::Load()
{

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof bd);

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(T);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;


	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Dx11Render::instance()->getDevice(device);

	auto result = device->CreateBuffer(&bd, nullptr, mConstantBuffer.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}
}

template<class T>
void ConstantBuffer<T>::Reset()
{
	mConstantBuffer.Reset();
}

template<class T>
void ConstantBuffer<T>::UpdateBuffer(const T & pData)
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Dx11Render::instance()->getDeviceContext(deviceContext);

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