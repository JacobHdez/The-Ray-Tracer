#pragma once

#include "../Vertex.h"

class Primitive
{
public:
	virtual ~Primitive();

	const std::vector<Vertex>& GetVertices() const { return m_Vertices; }
	const std::vector<unsigned int>& GetIndices() const { return m_Indices; }
protected:
	void Set(const Vertex* vertices, const unsigned int numVertices, const unsigned int* indices, const unsigned int numIndices);
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
};

class Plane : public Primitive
{
public:
	Plane();
	virtual ~Plane();
};

class Cube : public Primitive
{
public:
	Cube();
	virtual ~Cube();
};

/*class Sphere : public Primitive
{
public:
	Sphere();
	virtual ~Sphere();
};*/

/*class NonhierCube : public Primitive
{
public:
	NonhierCube(glm::vec3 position, float size);
	virtual ~NonhierCube();
private:
	glm::vec3 m_Position;
	float m_Size;
};*/

/*class NonhierSphere : public Primitive
{
public:
	NonhierSphere(glm::vec3 position, float radius);
	virtual ~NonhierSphere();
private:
	glm::vec3 m_Position;
	float m_Radius;
};*/