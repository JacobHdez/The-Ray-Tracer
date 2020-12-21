#pragma once

#include "Mesh/Mesh.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	Model(const std::string& path);

	void Setup();
	void Draw(const GLCore::Utils::Shader* shader);
private:
	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
};