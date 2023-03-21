#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 Color;

uniform mat4 u_model = mat4(1.0);
uniform mat4 u_viewProjection = mat4(1.0);

void main()
{
    gl_Position = u_viewProjection * u_model * vec4(aPos, 1.0);
	Color = aColor;
}