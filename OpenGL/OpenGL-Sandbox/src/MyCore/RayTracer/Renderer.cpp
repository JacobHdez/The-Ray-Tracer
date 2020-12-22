#include "Renderer.h"

void RTRender(Scene& scene, unsigned int width, unsigned int height, std::string imgName)
{
	// Image
	float aspect_ratio = (float) width / height;

	// Camera
	float viewport_height = 2.0f;
	float viewport_width = scene.GetAspect() * viewport_height;
	float focal_length = 1.0f;

	glm::vec3 origin = scene.GetCameraPosition();
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
			if (count % 3000 == 0)
			{
				buff = Convert(count / nPixels * 100.0f) + "%";
				LOG_INFO(buff.c_str());
			}

			float u = float(i) / (width - 1);
			float v = float(j) / (height - 1);
			Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			glm::vec3 pixel_color = ray_color(scene, ray, 0);

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

glm::vec3 ray_color(Scene& scene, Ray& primRay, int depth)
{
	hit_record hit;
	float minDist = FLT_MAX; // std::numeric_limits<float>::max();

	bool hitMesh = false;
	std::list<SceneNode> objects = scene.GetNodes();
	auto hitObject = objects.begin();

	// for (auto& it : objects)
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		if (Intersect(*it, primRay, hit))
		{
			float distance = glm::distance(scene.GetCameraPosition(), hit.m_Point);
			if (distance < minDist)
			{
				hitMesh = true;
				hitObject = it;
			}
		}
	}

	if (!hitMesh) // Background
	{
		glm::vec3 uDir = glm::normalize(primRay.GetDirection());
		float t = 0.5f * (uDir.y + 1.0f);
		return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.1f, 0.3f, 0.4f);
	}

	glm::vec3 hitColor;

	Material material = hitObject->GetMaterial();
	for (auto& it : scene.GetLights())
	{
		// Ambient
		glm::vec3 ambient = it.GetColor() * material.GetAmbient();

		// Difusse
		glm::vec3 lightDir = glm::normalize(it.GetPosition() - hit.m_Point);
		float diff = std::max(glm::dot(hit.m_Normal, lightDir), 0.0f);
		glm::vec3 difusse = it.GetColor() * (diff * material.GetDiffuse());

		// Specular
		glm::vec3 cameraDir = glm::normalize(scene.GetCameraPosition() - hit.m_Point);
		glm::vec3 reflectDir = glm::reflect(-lightDir, hit.m_Normal);
		float spec = std::pow(std::max(glm::dot(cameraDir, reflectDir), 0.0f), material.GetShininess());
		glm::vec3 specular = it.GetColor() * (spec * material.GetSpecular());

		float distance = glm::length(it.GetPosition() - hit.m_Point);
		float attenuation = 1.0f / (it.GetConstant() + it.GetLinear() * distance + it.GetQuadratic() * (distance * distance));

		ambient *= attenuation;
		difusse *= attenuation;
		specular *= attenuation;

		hitColor = ambient + difusse + specular;
	}

	return hitColor;
}

bool Intersect(SceneNode& node, Ray& ray, hit_record& hit)
{
	bool intersect = false;
	float tNear = FLT_MAX;

	glm::mat4 modelMatrix = node.GetModelMatrix();
	glm::mat4 invModelMatrix = node.GetInvModelMatrix();

	for (int i = 0; i < node.GetNumFaces(); ++i)
	{
		std::vector<Vertex> vertices = node.GetFace(i);
		vertices[0].Position = modelMatrix * glm::vec4(vertices[0].Position, 1.0f);
		vertices[1].Position = modelMatrix * glm::vec4(vertices[1].Position, 1.0f);
		vertices[2].Position = modelMatrix * glm::vec4(vertices[2].Position, 1.0f);

		auto test = modelMatrix * glm::vec4(1.0f);

		glm::vec3 normalF = glm::transpose(invModelMatrix) * glm::vec4(node.GetNormal(i), 1.0f);

		float t = FLT_MAX;
		if (IntersectTriangle(vertices, normalF, ray, t) && t < tNear)
		{
			hit.m_Point = ray.at(t);
			hit.m_Normal = glm::normalize(normalF);
			hit.t = t;

			tNear = t;
			intersect = true;
		}
	}

	return intersect;
}

bool IntersectTriangle(std::vector<Vertex>& vertices, glm::vec3& normal, Ray& ray, float& t)
{
	glm::vec3 edge1 = vertices[1].Position - vertices[0].Position;
	glm::vec3 edge2 = vertices[2].Position - vertices[0].Position;
	glm::vec3 pvec = glm::cross(ray.GetDirection(), edge2);
	float det = glm::dot(edge1, pvec);
	if (det <= 0) return false;

	glm::vec3 tvec = ray.GetOrigin() - vertices[0].Position;
	float u = glm::dot(tvec, pvec);
	if (u < 0 || u > det) return false;

	glm::vec3 qvec = glm::cross(tvec, edge1);
	float v = glm::dot(ray.GetDirection(), qvec);
	if (v < 0 || u + v > det) return false;

	float invDet = 1 / det;

	t = glm::dot(edge2, qvec) * invDet;

	return true;

	/*float NdotRayDirection = glm::dot(normal, ray.GetDirection());
	if (fabs(NdotRayDirection) < EPSILON)
		return false;

	float d = glm::dot(normal, vertices[0].Position);

	t = (glm::dot(normal, ray.GetOrigin()) + d) / NdotRayDirection;
	if (t < 0) return false;

	glm::vec3 P = ray.at(t);

	glm::vec3 C;

	glm::vec3 edge0 = vertices[1].Position - vertices[0].Position;
	glm::vec3 vp0 = P - vertices[0].Position;
	C = glm::cross(edge0, vp0);
	if (glm::dot(normal, C) < 0.0f) return false;

	glm::vec3 edge1 = vertices[2].Position - vertices[1].Position;
	glm::vec3 vp1 = P - vertices[1].Position;
	C = glm::cross(edge1, vp1);
	if (glm::dot(normal, C) < 0.0f) return false;

	glm::vec3 edge2 = vertices[0].Position - vertices[2].Position;
	glm::vec3 vp2 = P - vertices[2].Position;
	C = glm::cross(edge2, vp2);
	if (glm::dot(normal, C) < 0.0f) return false;

	return true;*/
}

std::string Convert(float number)
{
	std::ostringstream buff;
	buff << std::fixed;
	buff << std::setprecision(2);
	buff << number;
	return buff.str();
}