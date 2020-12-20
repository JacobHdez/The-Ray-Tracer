#include "Primitive.h"

Primitive::~Primitive()
{
}

void Primitive::Set(const char* name, const Vertex* vertices, const unsigned int numVertices, const unsigned int* indices, const unsigned int numIndices)
{
	m_Name = name;
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
		glm::vec3( 1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
	};
	unsigned int numVertices = sizeof(vertices) / sizeof(Vertex);

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3,
		2, 3, 7,
		2, 6, 7,
		0, 2, 4,
		2, 4, 6,
		1, 3, 7,
		1, 5, 7,
		4, 6, 7,
		4, 5, 7,
		0, 1, 4,
		1, 4, 5
	};
	unsigned int numIndices = sizeof(indices) / sizeof(unsigned int);

	Set("Cube", vertices, numVertices, indices, numIndices);
}

Cube::~Cube()
{
}