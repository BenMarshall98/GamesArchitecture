#pragma once

#ifdef DX_11

#include <wrl/client.h>
#include <d3d11.h>

#include "Texture.h"

class DirectXTexture final : public Texture
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture = nullptr;

public:
	explicit DirectXTexture(const std::string & pTextureFile) : Texture(pTextureFile) {}
	~DirectXTexture() = default;

	DirectXTexture(const DirectXTexture &) = delete;
	DirectXTexture(DirectXTexture &&) = delete;
	DirectXTexture & operator= (const DirectXTexture &) = delete;
	DirectXTexture & operator= (DirectXTexture &&) = delete;

	bool Load() override;
	void Use(unsigned int pIndex) const override;
};

#endif