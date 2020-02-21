#include "FragmentShader.h"
#include "Dx11Render.h"

bool FragmentShader::Load()
{
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr;

	auto result = CompileShader("ps_5_0", psBlob.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Dx11Render::instance()->getDevice(device);

	result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, mPixelShader.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void FragmentShader::Reset()
{
	mPixelShader.Reset();
}

void FragmentShader::UseProgram()
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Dx11Render::instance()->getDeviceContext(deviceContext);

	deviceContext->PSSetShader(mPixelShader.Get(), nullptr, 0);
}