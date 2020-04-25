#include "DirectXTexture.h"

#ifdef DX_11

#include <codecvt>

#include "DDSTextureLoader.h"
#include "DirectXRenderManager.h"

bool DirectXTexture::Load()
{
	const auto temp = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(mTextureFile);
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	const auto result = DirectX::CreateDDSTextureFromFile(device.Get(), temp.c_str(), nullptr, mTexture.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void DirectXTexture::Use(const unsigned int pIndex) const
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	deviceContext->PSSetShaderResources(pIndex, 1, mTexture.GetAddressOf());
}

#endif