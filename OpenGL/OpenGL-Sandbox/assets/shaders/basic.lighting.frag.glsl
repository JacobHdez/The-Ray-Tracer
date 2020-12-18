# version 330 core

out vec4 o_Color;

uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;
uniform vec3 u_objectColor;
uniform vec3 u_cameraPosition;

in vec3 o_Position;
in vec3 o_Normal;

void main()
{
	// ----- Ambient lighting ----------
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_lightColor;
	// ---------------------------------

	// ----- Diffuse lighting ----------
	vec3 norm = normalize(o_Normal);
	vec3 lightDir = normalize(u_lightPosition - o_Position);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;
	// ---------------------------------

	// ----- Specular Lighting ---------
	float specularStrength = 0.5;

	vec3 cameraDir = normalize(u_cameraPosition - o_Position);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_lightColor;  
	// ---------------------------------

	vec3 result = (ambient + diffuse + specular) * u_objectColor;
	o_Color = vec4(result, 1.0f);
}