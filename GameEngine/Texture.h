#pragma once

#include <d3d11.h>
#include <string>
#include <wrl/client.h>

class Texture
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture = nullptr;
	std::string mTextureFile;

public:
	explicit Texture(const std::string & pTextureFile);
	~Texture() = default;

	Texture(const Texture &) = delete;
	Texture(Texture &&) = delete;
	Texture & operator = (const Texture &) = delete;
	Texture & operator = (Texture &&) = delete;

	bool Load();
	
	void Use(unsigned int pIndex) const;
};

