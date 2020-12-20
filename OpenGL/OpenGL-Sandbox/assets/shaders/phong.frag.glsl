#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 vs_Position;
in vec3 vs_Normal;

out vec4 fragColor;

uniform Material material;

uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
uniform vec3 u_CameraPos;

void main()
{
	// ----- Ambient lighting ----------
	vec3 ambient = u_LightColor * material.ambient;

	// ----- Diffuse lighting ----------
	vec3 norm = normalize(vs_Normal);
	vec3 lightDir = normalize(u_LightPos - vs_Position);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_LightColor * (diff * material.diffuse);

	// ----- Specular Lighting ----------
	vec3 cameraDir = normalize(u_CameraPos - vs_Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
	vec3 specular = u_LightColor * (spec * material.specular);

	// ----- Result ----------
	vec3 result = ambient + diffuse + specular;
	fragColor = vec4(result, 1.0f);
}