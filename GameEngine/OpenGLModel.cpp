#include "OpenGLModel.h"

#include "ModelLoader.h"

#ifdef GL_430

#include "OpenGL.h"

OpenGLModel::~OpenGLModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

bool OpenGLModel::Load()
{
	std::vector<VertexData> mesh;
	std::vector<unsigned int> indices;

	ModelLoader::LoadModelFromFile(mModelFile, mesh, indices);

	mIndexSize = indices.size();
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return true;
}

void OpenGLModel::Render()
{
	if (this != mLastModel)
	{
		glBindVertexArray(VAO);
		mLastModel = this;
	}

	glDrawElements(GL_TRIANGLES, mIndexSize, GL_UNSIGNED_INT, nullptr);
}

#endif