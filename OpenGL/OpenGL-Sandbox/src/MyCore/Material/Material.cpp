#include "Material.h"

using namespace GLCore;
using namespace GLCore::Utils;

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
	: m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess)
{
}

Material::Material(const Material& material)
{
	m_Ambient = material.m_Ambient;
	m_Diffuse = material.m_Diffuse;
	m_Specular = material.m_Specular;
	m_Shininess = material.m_Shininess;
}

Material::~Material()
{
}

void Material::SendToShader(Shader* shader)
{
	int location = glGetUniformLocation(shader->GetRendererID(), "material.diffuse");
	glUniform3fv(location, 1, glm::value_ptr(m_Diffuse));
	location = glGetUniformLocation(shader->GetRendererID(), "material.specular");
	glUniform3fv(location, 1, glm::value_ptr(m_Specular));
	location = glGetUniformLocation(shader->GetRendererID(), "material.shininess");
	glUniform1f(location, m_Shininess);
}