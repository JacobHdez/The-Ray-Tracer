	#include "Primitive.h"

Primitive::~Primitive()
{
}

void Primitive::Set(const Vertex* vertices, const unsigned int numVertices, const unsigned int* indices, const unsigned int numIndices)
{
	for (size_t i = 0; i < numVertices; ++i)
	{
		m_Vertices.push_back(vertices[i]);
	}
	for (size_t i = 0; i < numIndices; ++i)
	{
		m_Indices.push_back(indices[i]);
	}
}

Cube::Cube()
	: Primitive()
{
	Vertex vertices[] = {
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
	};
	unsigned int numVertices = sizeof(vertices) / sizeof(Vertex);

	unsigned int indices[] = {
		4, 2, 0,
		2, 7, 3,
		6, 5, 7,
		1, 7, 5,
		0, 3, 1,
		4, 1, 5,
		4, 6, 2,
		2, 6, 7,
		6, 4, 5,
		1, 3, 7,
		0, 2, 3,
		4, 0, 1
	};
	unsigned int numIndices = sizeof(indices) / sizeof(unsigned int);

	Set(vertices, numVertices, indices, numIndices);
}

Cube::~Cube()
{
}