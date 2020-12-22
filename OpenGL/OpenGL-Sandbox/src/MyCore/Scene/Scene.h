#pragma once

#include "Mesh/Mesh.h"
#include "Material/Material.h"
#include "Light/Light.h"

//class SceneNode
//{
//public:
//
//	void SetModelMatrix(const glm::mat4& model) { m_Model = model; }
//	const glm::mat4& GetModelMatrix() const { return m_Model; }
//private:
//	int m_ID;
//
//	SceneNode* m_Parent;
//	std::vector<SceneNode*> m_Children;
//};
class SceneNode
{
public:
	SceneNode(const std::string& name, const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix);
	SceneNode(const SceneNode& node);
	~SceneNode();

	void Setup();
	void Draw(GLCore::Utils::Shader* shader);

	int GetNumFaces() const { return m_Mesh.GetNumFaces(); }
	std::vector<Vertex> GetFace(int nFace) { return m_Mesh.GetFace(nFace); }
	glm::vec3 GetNormal(int nFace) { return m_Mesh.GetNormal(nFace); }
	glm::mat4 GetModelMatrix() const { return m_ModelMatrix; }
private:
	std::string m_Name;

	Mesh m_Mesh;
	Material m_Material;

	glm::mat4 m_ModelMatrix;
};

class Scene
{
public:
	Scene(const std::string& filepath);
	~Scene();

	void Setup();
	void Draw(GLCore::Utils::Shader* shader);

	float GetAspect() const { return m_aspect; }
	glm::vec3 GetCameraPosition() const { return m_Camera.GetPosition(); }
	const std::list<SceneNode> GetNodes() const { return m_Nodes; }
private:
	void LoadSceneScript(const std::string& filepath);
private:
	GLCore::Utils::PerspectiveCamera m_Camera;
	float m_fovy, m_aspect, m_zNear, m_zFar;

	std::vector<Light> m_Lights;

	//SceneNode* m_Root;
	std::list<SceneNode> m_Nodes;
};