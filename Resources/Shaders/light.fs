#version 330 core

out vec4 FragColor;

uniform vec3 u_lightColor = vec3(1.0f, 1.0f, 1.0f);

void main()
{
    FragColor = vec4(u_lightColor, 1.0f);
} 