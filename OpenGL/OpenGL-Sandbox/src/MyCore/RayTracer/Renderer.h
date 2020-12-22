#pragma once

#include "Ray.h"
#include "Scene/Scene.h"

constexpr auto MAX_RAY_DEPTH = 1;
constexpr auto EPSILON = 1e-1;

void RTRender(Scene& scene, unsigned int width, unsigned int height, std::string imgName);

glm::vec3 ray_color(Scene& scene, Ray& primRay, int depth);
bool Intersect(SceneNode& node, Ray& ray, hit_record& hit);
bool IntersectTriangle(std::vector<Vertex>& vertices, glm::vec3& normal, Ray& ray, float& t);

// Utils
std::string Convert(float number);