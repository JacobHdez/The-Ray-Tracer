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
	float nPixels = (float)(width * height) * 3.0f;
	int count = 0;
	std::string buff;

	unsigned char* pixels = new unsigned char[3 * width * height];
	for (int j = height - 1; j >= 0; --j)
	{
		for (int i = 0; i < width; ++i)
		{
			if (count % 1000 == 0)
			{
				buff = Convert(count / nPixels * 100.0f) + "%";
				LOG_INFO(buff.c_str());
			}

			float u = float(i) / (width - 1);
			float v = float(j) / (height - 1);
			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			glm::vec3 pixel_color = ray_color(ray);

			pixels[count++] = (unsigned int)(pixel_color.x * 255);
			pixels[count++] = (unsigned int)(pixel_color.y * 255);
			pixels[count++] = (unsigned int)(pixel_color.z * 255);
		}
	}
	std::string imagePath = "outputs/" + imgName + ".png";
	stbi_write_png(imagePath.c_str(), width, height, 3, pixels, 3 * width * sizeof(unsigned char));
	delete[] pixels;

	buff = Convert(count / nPixels * 100.0f) + "%";
	LOG_INFO(buff.c_str());
}

float hit_sphere(const glm::vec3& center, float radius, Ray& ray) {
	glm::vec3 oc = ray.GetOrigin() - center;
	auto a = glm::dot(ray.GetDirection(), ray.GetDirection());
	auto b = 2.0f * glm::dot(oc, ray.GetDirection());
	auto c = glm::dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
	{
		return -1.0f;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}

glm::vec3 ray_color(Ray& ray)
{
	float t = hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, ray);
	if (t > 0.0f)
	{
		glm::vec3 N = glm::normalize(ray.at(t) - glm::vec3(0.0f, 0.0f, -1.0f));
		return 0.5f * glm::vec3(N.x + 1.0f, N.y + 1.0f, N.z + 1.0f);
	}

	glm::vec3 uDir = glm::normalize(ray.GetDirection());
	float t = 0.5f * (uDir.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

std::string Convert(float number)
{
	std::ostringstream buff;
	buff << std::fixed;
	buff << std::setprecision(2);
	buff << number;
	return buff.str();
}