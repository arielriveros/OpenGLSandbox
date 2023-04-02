#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;


out vec2 TexCoord;
out vec3 FragPos;
out mat3 TBN;

uniform mat4 u_model = mat4(1.0);
uniform mat4 u_viewProjection = mat4(1.0);

void main()
{
	TexCoord = aTexCoord;
	mat3 normalMatrix = mat3(u_model);
	vec3 N = normalize(normalMatrix * aNormal);
	vec3 T = normalize(normalMatrix * aTangent);
	vec3 B = normalize(normalMatrix * aBitangent);
	//vec3 B = normalize(cross(N, T));
	TBN = mat3(T, B, N);
	FragPos = vec3(u_model * vec4(aPos, 1.0f));
	gl_Position = u_viewProjection * vec4(FragPos, 1.0);
}