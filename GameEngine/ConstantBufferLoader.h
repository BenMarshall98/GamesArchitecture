#pragma once

#include <memory>
#include "DirectXConstantBuffer.h"
#include "OpenGLConstantBuffer.h"

template <class T>
class ConstantBufferLoader final
{
	ConstantBufferLoader() = default;
	~ConstantBufferLoader() = default;

public:
	ConstantBufferLoader(const ConstantBufferLoader &) = delete;
	ConstantBufferLoader(ConstantBufferLoader &&) = delete;
	ConstantBufferLoader & operator= (const ConstantBufferLoader &) = delete;
	ConstantBufferLoader & operator= (ConstantBufferLoader &&) = delete;

	static std::unique_ptr<ConstantBuffer<T>> CreateConstantBuffer(int pVsSlot = -1, int pPsSlot = -1)
	{
#ifdef DX_11
		return std::move(std::make_unique<DirectXConstantBuffer<T>>(pVsSlot, pPsSlot));
#elif GL_430
		return std::move(std::make_unique<OpenGLConstantBuffer<T>>(pVsSlot));
#endif
	}
};