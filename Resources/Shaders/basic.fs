#version 330 core

in vec3 Color;
out vec4 FragColor;

uniform vec3 ColorModifier;

void main()
{
    FragColor = vec4(Color.x * ColorModifier.x, Color.y * ColorModifier.y, Color.z * ColorModifier.z, 1.0f);
} 