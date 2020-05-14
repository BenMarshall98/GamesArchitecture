#include "OpenGLModelInstanced.h"

#include "ModelLoader.h"

#ifdef GL_430

#include "OpenGL.h"

OpenGLModelInstanced::OpenGLModelInstanced(const std::string& pModelFile) : ModelInstanced(pModelFile)
{	
}

bool OpenGLModelInstanced::Load()
{
	std::vector<VertexData> mesh;
	std::vector<unsigned int> indices;

	ModelLoader::LoadModelFromFile(mModelFile, mesh, indices);

	mIndexSize = indices.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VIO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(VertexData), &mesh[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, VIO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(1 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return true;
}

void OpenGLModelInstanced::Render(const std::vector<glm::mat4>& pBuffer)
{
	if (this != mLastModel)
	{
		glBindVertexArray(VAO);
		mLastModel = this;
	}

	glBindBuffer(GL_ARRAY_BUFFER, VIO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * pBuffer.size(), pBuffer.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, mIndexSize, GL_UNSIGNED_INT, nullptr, pBuffer.size());
}

#endif