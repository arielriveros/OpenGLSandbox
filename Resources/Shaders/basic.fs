#version 330 core

in vec3 Color;
out vec4 FragColor;

uniform vec3 u_ColorModifier;

void main()
{
    FragColor = vec4(Color.x * u_ColorModifier.x, Color.y * u_ColorModifier.y, Color.z * u_ColorModifier.z, 1.0f);
} 