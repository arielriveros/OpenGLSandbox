#version 330 core

in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec3 u_lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 u_lightPos = vec3(0.0f, 0.0f, 0.0f);  

void main()
{
	float ambient  = 0.1f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(u_lightPos - FragPos);
	float diffuse = max(dot(normal, lightDirection), ambient);
	FragColor = texture(u_Texture, TexCoord) * vec4( u_lightColor * diffuse, 1.0f) * vec4(Color, 1.0);
}