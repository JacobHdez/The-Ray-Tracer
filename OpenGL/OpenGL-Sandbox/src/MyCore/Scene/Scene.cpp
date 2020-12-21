#include "Scene.h"

SceneNode::SceneNode()
	: m_Parent{ nullptr }, m_Mesh{ nullptr }, m_Material{ nullptr }, m_Model(glm::mat4(1.0f))
{
}

SceneNode::~SceneNode()
{
}

Scene::Scene(float fovy, float aspect, float zNear, float zFar)
	: m_Root{ nullptr }, m_Camera{ fovy, aspect, zNear, zFar }
{
}

Scene::~Scene()
{
}