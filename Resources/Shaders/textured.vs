#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform float yPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y + yPos, aPos.z, 1.0);
	Color = aColor;
	TexCoord = aTexCoord;
}