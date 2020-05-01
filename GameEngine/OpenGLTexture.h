#pragma once

#ifdef GL_430

#include "Texture.h"

class OpenGLTexture final : public Texture
{
	unsigned int mTexture;

public:
	OpenGLTexture(const std::string & pTextureFile) : Texture(pTextureFile) {}
	~OpenGLTexture();

	OpenGLTexture(const OpenGLTexture &) = delete;
	OpenGLTexture(OpenGLTexture &&) = delete;
	OpenGLTexture & operator= (const OpenGLTexture &) = delete;
	OpenGLTexture & operator= (OpenGLTexture &&) = delete;

	bool Load() override;
	void Use(unsigned int pIndex) const override;
};

#endif