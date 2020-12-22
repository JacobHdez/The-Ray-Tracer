#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

class Material
{
public:
	Material(glm::vec3 diffuse, glm::vec3 specular, float shininess);
	~Material();

	void SendToShader(GLCore::Utils::Shader* shader);
private:
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	float m_Shininess;
};