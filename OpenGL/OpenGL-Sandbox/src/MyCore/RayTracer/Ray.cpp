#include "Ray.h"

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction)
	: m_Origin(origin), m_Direction(direction)
{
}

Ray::Ray(const Ray& ray)
{
	m_Origin = ray.m_Origin;
	m_Direction = ray.m_Direction;
}

Ray::~Ray()
{
}