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
		glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
	};
	unsigned int numVertices = sizeof(vertices) / sizeof(Vertex);

	unsigned int indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};
	unsigned int numIndices = sizeof(indices) / sizeof(unsigned int);

	Set("Cube", vertices, numVertices, indices, numIndices);
}

Cube::~Cube()
{
}