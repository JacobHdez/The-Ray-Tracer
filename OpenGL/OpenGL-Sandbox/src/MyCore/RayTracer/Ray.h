#pragma once

#include <GLCore.h>

class Ray
{
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	Ray(const Ray& ray);
	~Ray();

	void SetOrigin(const glm::vec3& origin) { m_Origin = origin; }
	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	glm::vec3 GetOrigin() { return m_Origin; }
	glm::vec3 GetDirection() { return m_Direction; }

	glm::vec3 at(float t) const { return m_Origin + t * m_Direction; }
private:
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;
};