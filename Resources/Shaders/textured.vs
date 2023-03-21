#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 u_transform = mat4(1.0);

void main()
{
    gl_Position = u_transform * vec4(aPos, 1.0);
	Color = aColor;
	TexCoord = aTexCoord;
}