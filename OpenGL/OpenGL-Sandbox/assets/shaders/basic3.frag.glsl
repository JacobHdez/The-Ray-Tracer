# version 330 core

layout (location = 0) out vec4 o_Color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
	o_Color = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
}