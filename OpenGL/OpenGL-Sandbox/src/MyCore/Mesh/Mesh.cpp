#include "Mesh.h"

using namespace GLCore;
using namespace GLCore::Utils;

Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	: m_Name(name), m_Vertices(vertices), m_Indices(indices)
{
	Mesh::Setup();
}

Mesh::Mesh(const Primitive& primitive)
	: m_Name(primitive.GetName()), m_Vertices(primitive.GetVertices()), m_Indices(primitive.GetIndices())
{
	Mesh::Setup();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(const Shader* shader)
{
	// glUseProgram(shader.GetRendererID());

	m_va.Bind();
	m_ib.Bind();
	glDrawElements(GL_TRIANGLES, m_ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::Setup()
{
	m_va.Setup();

	m_vb.Setup(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex));

	m_layout.Push<float>(3); // Position
	m_layout.Push<float>(3); // Normal
	m_va.AddBuffer(m_vb, m_layout);

	m_ib.Setup(&m_Indices[0], m_Indices.size());

	m_vb.Unbind();
	m_va.Unbind();
	m_ib.Unbind();
}