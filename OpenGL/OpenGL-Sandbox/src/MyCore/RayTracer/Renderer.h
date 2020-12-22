#pragma once

#include "Ray.h"
#include "Scene/Scene.h"

void RTRender(Scene& scene, unsigned int width, unsigned int height, std::string imgName);

glm::vec3 ray_color(Ray& ray);

std::string Convert(float number);