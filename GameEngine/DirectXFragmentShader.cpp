#include "DirectXFragmentShader.h"

#ifdef DX_11

#include "DirectXRenderManager.h"

bool DirectXFragmentShader::Load()
{
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr;

	auto result = CompileShader("ps_5_0", psBlob.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, mPixelShader.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void DirectXFragmentShader::Reset()
{
	mPixelShader.Reset();
}

void DirectXFragmentShader::UseProgram()
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	deviceContext->PSSetShader(mPixelShader.Get(), nullptr, 0);
}

#endif