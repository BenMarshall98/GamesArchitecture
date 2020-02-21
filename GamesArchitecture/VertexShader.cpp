#include "VertexShader.h"
#include "Dx11Render.h"

bool VertexShader::Load()
{
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr;

	auto result = CompileShader("vs_5_0", vsBlob.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Dx11Render::instance()->getDevice(device);

	result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, mVertexShader.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	static const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	static const UINT numElements = ARRAYSIZE(layout);

	result = device->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), mInputLayout.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void VertexShader::Reset()
{
	mVertexShader.Reset();
	mInputLayout.Reset();
}

void VertexShader::UseProgram()
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Dx11Render::instance()->getDeviceContext(deviceContext);

	deviceContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
	deviceContext->IASetInputLayout(mInputLayout.Get());
}