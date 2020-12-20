#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

out vec3 vs_Position;
out vec3 vs_Normal;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);

	vs_Position = vec3(u_Model * vec4(a_Position, 1.0f));
	vs_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
}