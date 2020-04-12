#include "Model.h"

#include "DX11Render.h"
#include "ModelLoader.h"

Model::Model(const std::string & pModelFile) : mModelFile(pModelFile)
{
}

bool Model::Load()
{
	std::vector<VertexData> mesh;
	std::vector<unsigned int> indices;

	ModelLoader::LoadModelFromFile(mModelFile, mesh, indices);
	
	mIndicesSize = indices.size();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Dx11Render::instance()->getDevice(device);

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
		//TODO: Log error
		return false;
	}

	//Create Index Buffer
	bufferDesc.ByteWidth = sizeof(unsigned int) * indices.size();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&initData, sizeof initData);
	initData.pSysMem = indices.data();

	result = device->CreateBuffer(&bufferDesc, &initData, &mIndicesBuffer);

	if (FAILED(result))
	{
		//TODO: Log error
		return false;
	}

	return true;
}

void Model::Render()
{
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;
	Dx11Render::instance()->getDeviceContext(deviceContext);

	static Model * lastModel = nullptr;

	const auto numberBuffers = 1;

	if (this != lastModel)
	{
		std::vector<ID3D11Buffer *> bufferArray;
		bufferArray.emplace_back(mMeshBuffer.Get());

		std::vector<UINT> strideArray;
		strideArray.emplace_back(sizeof(VertexData));

		std::vector<UINT> offsetArray;
		offsetArray.emplace_back(0);

		deviceContext->IASetVertexBuffers(0, numberBuffers, bufferArray.data(), strideArray.data(), offsetArray.data());
		deviceContext->IASetIndexBuffer(mIndicesBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		lastModel = this;
	}

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	deviceContext->DrawIndexed(mIndicesSize, 0, 0);
}