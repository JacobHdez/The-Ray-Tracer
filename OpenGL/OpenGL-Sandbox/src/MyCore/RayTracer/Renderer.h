#pragma once

#include "Ray.h"
#include "Scene/Scene.h"

constexpr auto MAX_RAY_DEPTH = 1;
constexpr auto EPSILON = 1e-1;

void RTRender(Scene& scene, unsigned int width, unsigned int height, std::string imgName);

glm::vec3 ray_color(Scene& scene, Ray& primRay, int depth);
bool Trace(std::list<SceneNode>& nodes, Ray& ray, hit_record& hit, std::list<SceneNode>::iterator& hitNode);
bool Intersect(SceneNode& node, Ray& ray, hit_record& hit);
bool IntersectTriangle(std::vector<Vertex>& vertices, glm::vec3& normal, Ray& ray, float& t);
glm::vec3 CalcPointLight(const PointLight& light, Material& material, glm::vec3& normal, glm::vec3& hitPos, glm::vec3& cameraDir);

// Utils
std::string Convert(float number);