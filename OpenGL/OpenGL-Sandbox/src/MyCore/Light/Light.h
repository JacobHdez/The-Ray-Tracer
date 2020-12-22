#pragma once

#include <GLCore.h>

class Light
{
public:
	Light();
	Light(const glm::vec3& color, const glm::vec3& position);
	Light(const Light& light);
	~Light();

	const glm::vec3& GetColor() const { return m_Color; }
	const glm::vec3& GetPosition() const { return m_Position; }
	void SetColor(const glm::vec3& color) { m_Color = color; }
	void SetPosition(const glm::vec3& position) { m_Position = position; }
private:
	glm::vec3 m_Color;
	glm::vec3 m_Position;
};