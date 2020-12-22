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

void Mesh::loadMesh(const std::string& path)
{
	LOG_INFO("Loading mesh - Assimp");
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string err = "ERROR::ASSIMP::";
		err += importer.GetErrorString();
		LOG_ERROR(err);
		return;
	}
	processNode(scene->mRootNode, scene);
	LOG_INFO("Mesh loaded - Assimp");
}

void Mesh::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

void Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		m_Vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
			m_Indices.push_back(face.mIndices[j]);
	}
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