#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 u_model = mat4(1.0);
uniform mat4 u_viewProjection = mat4(1.0);
uniform vec2 u_uvModifier = vec2(1.0);

void main()
{
	TexCoord = aTexCoord * u_uvModifier;
	Normal = mat3(u_model) * aNormal;
	FragPos = vec3(u_model * vec4(aPos, 1.0f));
	gl_Position = u_viewProjection * vec4(FragPos, 1.0);
}