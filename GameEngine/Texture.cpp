#include "Texture.h"

#include <codecvt>

#include "DDSTextureLoader.h"
#include "Dx11Render.h"

Texture::Texture(const std::string& pTextureFile) : mTextureFile(pTextureFile)
{
}

bool Texture::Load()
{
	const auto temp = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(mTextureFile);
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Dx11Render::instance()->getDevice(device);

	const auto result = DirectX::CreateDDSTextureFromFile(device.Get(), temp.c_str(), nullptr, mTexture.ReleaseAndGetAddressOf());

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Use(const unsigned int pIndex) const
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Dx11Render::instance()->getDeviceContext(deviceContext);

	deviceContext->PSSetShaderResources(pIndex, 1, mTexture.GetAddressOf());
}