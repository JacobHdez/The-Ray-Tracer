#include "Model.h"

#include "MyCore.h"

using namespace GLCore;
using namespace GLCore::Utils;

Model::Model(const std::string& path)
{
	Model::loadModel(path);
}

void Model::Setup()
{
	for (auto& it : m_Meshes)
	{
		it.Setup();
	}
}

void Model::Draw(const Shader* shader)
{
	for (auto& it : m_Meshes)
	{
		it.Draw(shader);
	}
}

void Model::loadModel(const std::string& path)
{
	LOG_INFO("Loading model - Assimp");
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string err = "ERROR::ASSIMP::";
		err += importer.GetErrorString();
		LOG_ERROR(err);
		return;
	}
	m_Directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
	LOG_INFO("Model loaded - Assimp");
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    return Mesh(vertices, indices);
}