# version 330 core

layout (location = 0) out vec4 o_Color;

in vec3 ourColor;

void main()
{
	o_Color = vec4(ourColor, 1.0);
}