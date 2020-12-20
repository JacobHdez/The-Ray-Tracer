#pragma once

#include "Vertex.h"
#include "Primitive/Primitive.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const Primitive& primitive);
	Mesh(const Mesh& mesh);
	~Mesh();

	void Setup();
	void Draw(const GLCore::Utils::Shader* shader);
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	// OpenGL - Renderer
	VertexArray m_va;
	VertexBuffer m_vb;
	VertexBufferLayout m_layout;
	IndexBuffer m_ib;
};