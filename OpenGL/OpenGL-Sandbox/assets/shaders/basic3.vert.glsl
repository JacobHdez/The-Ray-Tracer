# version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;
layout (location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0f);
	ourColor = a_Color;
	TexCoord = a_TexCoord;
}