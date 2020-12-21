#include "Scene.h"

#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
namespace pt = boost::property_tree

/*
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;

// Create a root
pt::ptree root;

// Load the json file in this ptree
pt::read_json("filename.json", root);
*/

//SceneNode::SceneNode()
//	: m_Parent{ nullptr }, m_Mesh{ nullptr }, m_Material{ nullptr }, m_Model(glm::mat4(1.0f))
//{
//}
//
//SceneNode::~SceneNode()
//{
//}

Scene::Scene(const std::string& filepath)
{
	Scene::LoadSceneScript();
}

Scene::~Scene()
{
}

void Scene::LoadSceneScript()
{

}