#pragma once

#include <GLCore.h>

class Ray
{
public:
	Ray(const glm::vec3& origin, const glm::vec3& direction);
	~Ray();

	void SetOrigin(const glm::vec3& origin) { m_Origin = origin; }
	void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
	glm::vec3 GetOrigin() { return m_Origin; }
	glm::vec3 GetDirection() { return m_Direction; }
private:
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;
};