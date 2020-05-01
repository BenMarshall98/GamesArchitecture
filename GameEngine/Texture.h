#pragma once

#include <string>

class Texture
{
protected:
	std::string mTextureFile;

public:
	explicit Texture(const std::string & pTextureFile);
	virtual ~Texture() = default;

	Texture(const Texture &) = delete;
	Texture(Texture &&) = delete;
	Texture & operator= (const Texture &) = delete;
	Texture & operator= (Texture &&) = delete;

	virtual bool Load() = 0;
	virtual void Use(unsigned int pIndex) const = 0;
};

