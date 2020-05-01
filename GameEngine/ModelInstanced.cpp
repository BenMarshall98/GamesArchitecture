#include "ModelInstanced.h"

#ifdef DX_11

#include "DirectXRenderManager.h"

bool ModelInstanced::loadModel(const std::vector<VertexData>& pMesh, const std::vector<unsigned>& pIndices)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	//None changing data for Vertex Buffers;
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof bufferDesc);

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof initData);

	const auto vertexSize = pMesh.size();

	bufferDesc.ByteWidth = sizeof(VertexData) * vertexSize;
	initData.pSysMem = pMesh.data();

	auto result = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);

	if (FAILED(result))
	{
		//TODO: Log error
		return false;
	}

	mIndicesSize = pIndices.size();

	ZeroMemory(&bufferDesc, sizeof bufferDesc);

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	bufferDesc.ByteWidth = sizeof(unsigned int) * mIndicesSize;

	ZeroMemory(&initData, sizeof initData);
	initData.pSysMem = pIndices.data();

	result = device->CreateBuffer(&bufferDesc, &initData, &mIndicesBuffer);

	if (FAILED(result))
	{
		//TODO: Log error
		return false;
	}

	return true;
}

void ModelInstanced::render(unsigned pInstances) const
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	//Draw particles

	const auto numberBuffers = 1;

	std::vector<ID3D11Buffer *> particleBufferArray;
	particleBufferArray.emplace_back(mVertexBuffer.Get());

	std::vector<UINT> particleStrideArray;
	particleStrideArray.emplace_back(sizeof(VertexData));

	std::vector<UINT> particleOffsetArray;
	particleOffsetArray.emplace_back(0);

	deviceContext->IASetVertexBuffers(0, numberBuffers, particleBufferArray.data(), particleStrideArray.data(), particleOffsetArray.data());
	deviceContext->IASetIndexBuffer(mIndicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->DrawIndexedInstanced(mIndicesSize, pInstances, 0, 0, 0);
}
#endif