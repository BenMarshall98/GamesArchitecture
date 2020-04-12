#define NOMINMAX

#include "ModelLoader.h"

#include <DirectXMath.h>
#include <vector>

#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

void ModelLoader::LoadModelFromFile(const std::string & pModelFile, std::vector<VertexData> & pMesh, std::vector<unsigned int> & pIndices)
{
	Assimp::Importer importer;
	const auto scene = importer.ReadFile(pModelFile,
		aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		//TODO: Log error
		return;
	}

	const auto mesh = scene->mMeshes[0];

	std::vector<VertexData> vertexData;

	for (auto i = 0u; i < mesh->mNumVertices; i++)
	{
		VertexData vertex;

		{
			const auto x = mesh->mVertices[i].x;
			const auto y = mesh->mVertices[i].y;
			const auto z = mesh->mVertices[i].z;
			vertex.mVertex = DirectX::XMFLOAT3(x, y, z);
		}

		//{
		//	const auto x = mesh->mTextureCoords[0][i].x;
		//	const auto y = mesh->mTextureCoords[0][i].y;
		//	vertex.mTexCoord = DirectX::XMFLOAT2(x, y);
		//}
		//
		//{
		//	const auto x = mesh->mNormals[i].x;
		//	const auto y = mesh->mNormals[i].y;
		//	const auto z = mesh->mNormals[i].z;
		//	vertex.mNormal = DirectX::XMFLOAT3(x, y, z);
		//}

		vertexData.push_back(vertex);
	}

	std::vector<unsigned int> indices;

	for (auto i = 0u; i < mesh->mNumFaces; i++)
	{
		const auto face = mesh->mFaces[i];

		for (auto j = 0u; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
}