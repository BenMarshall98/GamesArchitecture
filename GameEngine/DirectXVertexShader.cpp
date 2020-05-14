#include "DirectXVertexShader.h"

#ifdef DX_11

#include "DirectXRenderManager.h"

bool DirectXVertexShader::Load()
{
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr;

	auto result = CompileShader("vs_5_0", vsBlob.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

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
		static const D3D11_INPUT_ELEMENT_DESC layoutInstanced[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"MATRIX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{"MATRIX", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{"MATRIX", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			{"MATRIX", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
			
		};

		static const UINT numElementsInstanced = ARRAYSIZE(layoutInstanced);

		result = device->CreateInputLayout(layoutInstanced, numElementsInstanced, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), mInputLayout.ReleaseAndGetAddressOf());

		if (FAILED(result))
		{
			return false;
		}
	}

	return true;
}

void DirectXVertexShader::Reset()
{
	mVertexShader.Reset();
	mInputLayout.Reset();
}

void DirectXVertexShader::UseProgram()
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	deviceContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
	deviceContext->IASetInputLayout(mInputLayout.Get());
}

#endif