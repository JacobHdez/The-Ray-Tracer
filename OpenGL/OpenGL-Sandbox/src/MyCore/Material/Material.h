#pragma once

#include <GLCore.h>
#include <GLCoreUtils.h>

class Material
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	Material(const Material& material);
	~Material();

	glm::vec3 GetAmbient() const { return m_Ambient; }
	glm::vec3 GetDiffuse() const { return m_Diffuse; }
	glm::vec3 GetSpecular() const { return m_Specular; }
	float GetShininess() const { return m_Shininess; }

	void SendToShader(GLCore::Utils::Shader* shader);
private:
	glm::vec3 m_Ambient;
	glm::vec3 m_Diffuse;
	glm::vec3 m_Specular;
	float m_Shininess;
};