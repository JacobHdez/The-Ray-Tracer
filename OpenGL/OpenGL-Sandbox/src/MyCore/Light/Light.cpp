#include "Light.h"

Light::Light()
	: m_Color{ 1.0f, 1.0f , 1.0f }, m_Position{ 1.0f, 1.0f , 2.0f }
{
}

Light::Light(const glm::vec3& color, const glm::vec3& position)
	: m_Color(color), m_Position(position)
{
}

Light::Light(const Light& light)
{
	m_Color = light.m_Color;
	m_Position = light.m_Position;
}

Light::~Light()
{
}