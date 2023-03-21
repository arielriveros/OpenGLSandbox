#version 330 core

out vec4 FragColor;

uniform vec4 u_lightColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
    FragColor = u_lightColor;
} 