#version 330 core

out vec4 fragColor;

uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

void main()
{
	fragColor = vec4(u_ObjectColor * u_LightColor, 1.0f);
}