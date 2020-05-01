#define STB_IMAGE_IMPLEMENTATION

#include "OpenGLTexture.h"

#ifdef GL_430

#include "OpenGL.h"
#include "stb_image.h"

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &mTexture);
}

bool OpenGLTexture::Load()
{
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 5);

	int width, height, numChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char * const image = stbi_load(mTextureFile.c_str(), &width, &height, &numChannels, STBI_rgb_alpha);
	const bool success = image;

	if (success)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		int i = 0;
	}

	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	return success;
}

void OpenGLTexture::Use(unsigned pIndex) const
{
	glActiveTexture(GL_TEXTURE0 + pIndex);
	glBindTexture(GL_TEXTURE_2D, mTexture);
}

#endif