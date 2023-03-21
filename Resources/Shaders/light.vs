#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_model;
uniform mat4 u_viewProjection;

void main()
{
    gl_Position = u_viewProjection * u_model * vec4(aPos, 1.0);
} 