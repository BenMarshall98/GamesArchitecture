#pragma once

template <class T>
class ConstantBuffer
{
protected:
	int mVSSlot;
	int mPSSlot;

public:
	ConstantBuffer(int pVSSlot = -1, int pPSSlot = -1);
	virtual ~ConstantBuffer() = default;

	ConstantBuffer(const ConstantBuffer &) = delete;
	ConstantBuffer(ConstantBuffer &&) = delete;
	ConstantBuffer & operator= (const ConstantBuffer &) = delete;
	ConstantBuffer & operator= (ConstantBuffer &&) = delete;

	virtual bool Load() = 0;
	virtual void Reset() = 0;
	virtual void UpdateBuffer(const T & pData) = 0;
};

template <class T>
ConstantBuffer<T>::ConstantBuffer(int pVSSlot, int pPSSlot) : mVSSlot(pVSSlot), mPSSlot(pPSSlot)
{
}