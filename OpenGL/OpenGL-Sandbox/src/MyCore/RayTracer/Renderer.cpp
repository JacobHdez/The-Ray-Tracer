#include "Renderer.h"

void RTRender(Scene& scene, unsigned int width, unsigned int height, std::string imgName)
{
	// Image
	float aspect_ratio = (float) width / height;

	// Camera
	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;
	float focal_length = 1.0f;

	glm::vec3 origin(0.0f, 0.0f, 0.0f);
	glm::vec3 horizontal(viewport_width, 0.0f, 0.0f);
	glm::vec3 vertical(0.0f, viewport_height, 0.0f);
	glm::vec3 lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0.0f, 0.0f, focal_length);

	// Render
	float nPixels = (float)(width * height);
	unsigned int count = 0;
	std::string buff;

	unsigned char* pixels = new unsigned char[3 * width * height];
	for (unsigned int i = 0; i < height; ++i)
	{
		for (unsigned int j = 0; j < width; ++j)
		{
			if (count % 1000 == 0)
			{
				buff = Convert(count / nPixels * 100.0f) + "%";
				LOG_INFO(buff.c_str());
			}
			count++;

			// Test img
			pixels[0 + 3 * (j + width * i)] = ((float)i / (float)height) * 255;
			pixels[1 + 3 * (j + width * i)] = ((float)j / (float)width) * 255;
			pixels[2 + 3 * (j + width * i)] = ((i < height / 2.0f) && (j < width / 2.0f) ||
				(i >= height / 2.0f) && (j >= width / 2.0f)) ? 255 : 0;
		}
	}
	std::string imagePath = "outputs/" + imgName + ".png";
	stbi_write_png(imagePath.c_str(), width, height, 3, pixels, 3 * width * sizeof(unsigned char));
	delete[] pixels;

	buff = Convert(count / nPixels * 100.0f) + "%";
	LOG_INFO(buff.c_str());
}

glm::vec3 ray_color(Ray& ray)
{
	glm::vec3 uDir = glm::normalize(ray.GetDirection());
	float t = 0.5f * (uDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f);
}

std::string Convert(float number)
{
	std::ostringstream buff;
	buff << std::fixed;
	buff << std::setprecision(2);
	buff << number;
	return buff.str();
}
/*
return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
*/