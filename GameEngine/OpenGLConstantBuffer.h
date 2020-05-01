#pragma once

#ifdef GL_430

#include "ConstantBuffer.h"
#include "OpenGL.h"

template <class T>
class OpenGLConstantBuffer final : public ConstantBuffer<T>
{
	using ConstantBuffer<T>::mVSSlot;
	using ConstantBuffer<T>::mPSSlot;

	unsigned int mUbo;

public:
	OpenGLConstantBuffer(int pSlot = -1);
	~OpenGLConstantBuffer();

	OpenGLConstantBuffer(const OpenGLConstantBuffer &) = delete;
	OpenGLConstantBuffer(OpenGLConstantBuffer &&) = delete;
	OpenGLConstantBuffer & operator= (const OpenGLConstantBuffer &) = delete;
	OpenGLConstantBuffer & operator= (OpenGLConstantBuffer &&) = delete;

	bool Load() override;
	void Reset() override;
	void UpdateBuffer(const T & pData) override;
};

template <class T>
OpenGLConstantBuffer<T>::OpenGLConstantBuffer(int pSlot) : ConstantBuffer<T>(pSlot, pSlot)
{
}

template <class T>
OpenGLConstantBuffer<T>::~OpenGLConstantBuffer()
{
	glDeleteBuffers(1, &mUbo);
}

template <class T>
bool OpenGLConstantBuffer<T>::Load()
{
	glGenBuffers(1, &mUbo);
	
	glBindBuffer(GL_UNIFORM_BUFFER, mUbo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	glBindBufferRange(GL_UNIFORM_BUFFER, mVSSlot, mUbo, 0, sizeof(T));

	return true;
}

template <class T>
void OpenGLConstantBuffer<T>::Reset()
{
	glDeleteBuffers(1, &mUbo);
}

template <class T>
void OpenGLConstantBuffer<T>::UpdateBuffer(const T& pData)
{
	glBindBuffer(GL_UNIFORM_BUFFER, mUbo);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), &pData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

#endif