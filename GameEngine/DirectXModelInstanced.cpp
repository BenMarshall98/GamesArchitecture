#include "DirectXModelInstanced.h"

#ifdef DX_11

#include "RenderManager.h"
#include "DirectXRenderManager.h"
#include "ModelLoader.h"

DirectXModelInstanced::DirectXModelInstanced(const std::string& pModelFile) : ModelInstanced(pModelFile)
{
}

bool DirectXModelInstanced::Load()
{
	std::vector<VertexData> mesh;
	std::vector<unsigned int> indices;

	ModelLoader::LoadModelFromFile(mModelFile, mesh, indices);
	
	mIndicesSize = indices.size();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDevice(device);

	//None changing data for buffers;
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof bufferDesc);

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof initData);

	//Create Position Buffer
	bufferDesc.ByteWidth = sizeof(VertexData) * mesh.size();
	initData.pSysMem = mesh.data();

	auto result = device->CreateBuffer(&bufferDesc, &initData, &mMeshBuffer);

	if (FAILED(result))
	{
		return false;
	}

	//None changing data for Vertex Buffers;
	ZeroMemory(&bufferDesc, sizeof bufferDesc);
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//Create Particle Position Buffer
	bufferDesc.ByteWidth = sizeof(glm::mat4) * 1000;

	result = device->CreateBuffer(&bufferDesc, nullptr, &mModelBuffer);

	if (FAILED(result))
	{
		return false;
	}

	//Create Index Buffer
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	ZeroMemory(&initData, sizeof initData);
	initData.pSysMem = indices.data();

	result = device->CreateBuffer(&bufferDesc, &initData, &mIndicesBuffer);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void DirectXModelInstanced::Render(const std::vector<glm::mat4>& pBuffer)
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	dynamic_cast<DirectXRenderManager*>(RenderManager::Instance())->GetDeviceContext(deviceContext);

	D3D11_MAPPED_SUBRESOURCE mappedData;

	//Map Particle Positions
	ZeroMemory(&mappedData, sizeof mappedData);

	auto result = deviceContext->Map(mModelBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

	memcpy(mappedData.pData, pBuffer.data(), sizeof(glm::mat4) * pBuffer.size());

	deviceContext->Unmap(mModelBuffer.Get(), 0);
	
	//Draw particles

	const auto numberBuffers = 2u;

	if (this != mLastModel)
	{
		std::vector<ID3D11Buffer *> particleBufferArray;
		particleBufferArray.emplace_back(mMeshBuffer.Get());
		particleBufferArray.emplace_back(mModelBuffer.Get());

		std::vector<UINT> particleStrideArray;
		particleStrideArray.emplace_back(sizeof(VertexData));
		particleStrideArray.emplace_back(sizeof(glm::mat4));

		std::vector<UINT> particleOffsetArray;
		particleOffsetArray.emplace_back(0);
		particleOffsetArray.emplace_back(0);

		deviceContext->IASetVertexBuffers(0, numberBuffers, particleBufferArray.data(), particleStrideArray.data(), particleOffsetArray.data());
		deviceContext->IASetIndexBuffer(mIndicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mLastModel = this;
	}

	deviceContext->DrawIndexedInstanced(mIndicesSize, pBuffer.size(), 0, 0, 0);
}

#endif