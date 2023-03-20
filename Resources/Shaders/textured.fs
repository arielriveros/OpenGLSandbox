#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 u_ColorModifier;
uniform sampler2D u_Texture;

void main()
{
	FragColor = texture(u_Texture, TexCoord) * vec4(Color, 1.0) * vec4(u_ColorModifier, 1.0);
}