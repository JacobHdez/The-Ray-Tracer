#pragma once

#include "Vertex.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"

class Mesh
{
public:
	Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	void Draw(const GLCore::Utils::Shader* shader);
private:
	void Setup();
private:
	std::string m_Name;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	// OpenGL - Renderer
	VertexArray m_va;
	VertexBuffer m_vb;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;
};