#pragma once

#include "MyCore.h"

//class SceneNode
//{
//public:
//	SceneNode();
//	~SceneNode();
//
//	void SetModelMatrix(const glm::mat4& model) { m_Model = model; }
//	const glm::mat4& GetModelMatrix() const { return m_Model; }
//private:
//	int m_ID;
//	std::string m_Name;
//
//	SceneNode* m_Parent;
//	std::vector<SceneNode*> m_Children;
//
//	Mesh* m_Mesh;
//	Material* m_Material;
//
//	glm::mat4 m_Model;
//};

class Scene
{
public:
	Scene(const std::string& filepath);
	~Scene();

	void LoadSceneScript();
private:
};