#include "Scene.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

using namespace GLCore;
using namespace GLCore::Utils;

SceneNode::SceneNode(const std::string& name, const Mesh& mesh, const Material& material, const glm::mat4& modelMatrix)
	: m_Name(name), m_Mesh(mesh), m_Material(material), m_ModelMatrix(modelMatrix)
{
	m_invModelMatrix = glm::inverse(m_ModelMatrix);
}

SceneNode::SceneNode(const SceneNode& node)
	: m_Name(node.m_Name), m_Mesh(node.m_Mesh), m_Material(node.m_Material), m_ModelMatrix(node.m_ModelMatrix), m_invModelMatrix(node.m_invModelMatrix)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::Setup()
{
	m_Mesh.Setup();
}

void SceneNode::Draw(GLCore::Utils::Shader* shader)
{
	int location = glGetUniformLocation(shader->GetRendererID(), "u_Model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));
	m_Mesh.Draw();
}

Scene::Scene(const std::string& filepath)
	: m_Camera(45.0f, 16.0f / 9.0f, 0.01f, 1000.0f)
{
	Scene::LoadSceneScript(filepath);
}

Scene::~Scene()
{
}

void Scene::Setup()
{
	for (auto& it : m_Nodes)
	{
		it.Setup();
	}
}

void Scene::Draw(GLCore::Utils::Shader* shader)
{
	for (auto& it : m_Nodes)
	{
		it.Draw(shader);
	}
}

void Scene::LoadSceneScript(const std::string& filepath)
{
	LOG_INFO("[SCENE] Loading scene!");
	pt::ptree root;
	pt::read_json(filepath, root);


	LOG_INFO("[SCENE] Loading camera!");
	std::vector<float> aspect;

	m_fovy = root.get<float>("camera.fovy");
	for (pt::ptree::value_type& value : root.get_child("camera.aspect"))
	{
		aspect.push_back(value.second.get_value<float>());
	}
	m_aspect = aspect[0] / aspect[1];
	m_zNear = root.get<float>("camera.zNear");
	m_zFar = root.get<float>("camera.zFar");
	m_Camera.SetProjection(m_fovy, m_aspect, m_zNear, m_zFar);


	LOG_INFO("[SCENE] Loading light sources!");
	for (pt::ptree::value_type& light : root.get_child("light_sources"))
	{
		LOG_INFO("[SCENE::LIGHT] Loading light!");

		std::vector<float> color;
		for (pt::ptree::value_type& value : light.second.get_child("color"))
		{
			color.push_back(value.second.get_value<float>());
		}

		std::vector<float> position;
		for (pt::ptree::value_type& value : light.second.get_child("position"))
		{
			position.push_back(value.second.get_value<float>());
		}

		float constant = light.second.get<float>("constant");
		float linear = light.second.get<float>("linear");
		float quadratic = light.second.get<float>("quadratic");

		m_Lights.push_back(PointLight(glm::vec3(color[0], color[1], color[2]), glm::vec3(position[0], position[1], position[2]), constant, linear, quadratic));
	}

	LOG_INFO("[SCENE] Loading materials!");
	std::unordered_map<std::string, Material> materials;
	for (pt::ptree::value_type& material : root.get_child("materials"))
	{
		LOG_INFO("[SCENE::MATERIAL] Loading material!");
		std::string name = material.first.data();

		std::vector<float> ambient;
		for (pt::ptree::value_type& value : material.second.get_child("ambient"))
		{
			ambient.push_back(value.second.get_value<float>());
		}

		std::vector<float> diffuse;
		for (pt::ptree::value_type& value : material.second.get_child("diffuse"))
		{
			diffuse.push_back(value.second.get_value<float>());
		}

		std::vector<float> specular;
		for (pt::ptree::value_type& value : material.second.get_child("specular"))
		{
			specular.push_back(value.second.get_value<float>());
		}

		float shininess = material.second.get<float>("shininess");

		materials.insert(std::make_pair(name, Material(glm::vec3(ambient[0], ambient[1], ambient[2]), glm::vec3(diffuse[0], diffuse[1], diffuse[2]), glm::vec3(specular[0], specular[1], specular[2]), shininess)));
	}

	LOG_INFO("[SCENE] Loading objects!");
	for (pt::ptree::value_type& object : root.get_child("objects"))
	{
		LOG_INFO("[SCENE::OBJECTS] Loading object!");
		std::string name = object.first;

		std::vector<float> position;
		for (pt::ptree::value_type& value : object.second.get_child("position"))
		{
			position.push_back(value.second.get_value<float>());
		}
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position[0], position[1], position[2]));

		std::vector<float> rotation;
		for (pt::ptree::value_type& value : object.second.get_child("rotation"))
		{
			rotation.push_back(value.second.get_value<float>());
		}
		glm::vec3 EulerAngles(rotation[0], rotation[1], rotation[2]);
		glm::mat4 rotationMatrix = glm::toMat4(glm::quat(EulerAngles));

		std::vector<float> scale;
		for (pt::ptree::value_type& value : object.second.get_child("scale"))
		{
			scale.push_back(value.second.get_value<float>());
		}
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2]));

		glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		std::string material = object.second.get<std::string>("material");
		
		std::string buffer;
		bool isPrimitive = object.second.get<bool>("primitive");
		if (isPrimitive)
		{
			buffer = object.second.get<std::string>("type");
			if (!buffer.compare("cube"))
			{
				auto it = materials.find(material);
				if (it == materials.end())
				{
					material = "Material '" + material + "' not found.";
					LOG_WARN(material.c_str());
				}
				else
				{
					m_Nodes.push_back(SceneNode(name, Mesh(Cube()), it->second, modelMatrix));
				}
			}
			else if (!buffer.compare("plane"))
			{
				auto it = materials.find(material);
				if (it == materials.end())
				{
					material = "Material '" + material + "' not found.";
					LOG_WARN(material.c_str());
				}
				else
				{
					m_Nodes.push_back(SceneNode(name, Mesh(Plane()), it->second, modelMatrix));
				}
			}
			else
			{
				buffer = "The primitive '" + buffer + "' is not defined";
				LOG_WARN(buffer.c_str());
			}
		}
		else
		{
			buffer = object.second.get<std::string>("filepath");

			auto it = materials.find(material);
			if (it == materials.end())
			{
				material = "Material '" + material + "' not found.";
				LOG_WARN(material.c_str());
			}
			else
			{
				m_Nodes.push_back(SceneNode(name, Mesh(buffer), it->second, modelMatrix));
			}
		}
	}

	LOG_INFO("[SCENE] Scene loaded!");
}