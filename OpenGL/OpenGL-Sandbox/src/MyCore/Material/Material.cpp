#include "Material.h"

using namespace GLCore;
using namespace GLCore::Utils;

Material::Material(glm::vec3 diffuse, glm::vec3 specular, float shininess)
	: m_Diffuse(diffuse), m_Specular(specular), m_Shininess(shininess)
{
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