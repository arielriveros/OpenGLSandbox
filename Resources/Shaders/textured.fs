#version 330 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec4 u_lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	FragColor = texture(u_Texture, TexCoord) * u_lightColor * vec4(Color, 1.0);
}