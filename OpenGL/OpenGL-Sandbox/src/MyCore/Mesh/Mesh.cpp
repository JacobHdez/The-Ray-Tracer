#include "Mesh.h"

using namespace GLCore;
using namespace GLCore::Utils;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: m_Vertices(vertices), m_Indices(indices)
{
}

Mesh::Mesh(const Primitive& primitive)
	: m_Vertices(primitive.GetVertices()), m_Indices(primitive.GetIndices())
{
}

Mesh::Mesh(const Mesh& mesh)
{
	m_Vertices = mesh.m_Vertices;
	m_Indices = mesh.m_Indices;
}

Mesh::~Mesh()
{
}

void Mesh::Setup()
{
	m_va.Setup();

	m_vb.Setup(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));

	m_layout.Push<float>(3); // Position
	// m_layout.Push<float>(3); // Normal
	m_va.AddBuffer(m_vb, m_layout);

	m_ib.Setup(&m_Indices[0], m_Indices.size());

	m_vb.Unbind();
	m_va.Unbind();
	m_ib.Unbind();
}

void Mesh::Draw(const Shader* shader)
{
	// glUseProgram(shader.GetRendererID());

	m_va.Bind();
	m_ib.Bind();
	glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}