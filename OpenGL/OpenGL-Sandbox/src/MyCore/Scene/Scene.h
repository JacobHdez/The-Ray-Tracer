#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>
#include "MyCore.h"

class SceneNode
{
public:
	SceneNode();
	~SceneNode();

	void SetModelMatrix(const glm::mat4& model) { m_Model = model; }
	const glm::mat4& GetModelMatrix() const { return m_Model; }
private:
	int m_ID;
	std::string m_Name;

	SceneNode* m_Parent;
	std::vector<SceneNode*> m_Children;

	Mesh* m_Mesh;
	Material* m_Material;

	glm::mat4 m_Model;
};

class Scene
{
public:
	Scene(float fovy, float aspect, float zNear, float zFar);
	~Scene();

	void SetProjection(float fovy, float aspect, float zNear, float zFar) { m_Camera.SetProjection(fovy, aspect, zNear, zFar); }
private:
	SceneNode* m_Root;

	GLCore::Utils::PerspectiveCamera m_Camera;
	std::vector<Light> m_Lights;
};