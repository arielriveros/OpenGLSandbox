#version 330 core

in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D u_Texture;
uniform vec3 u_lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 u_lightPos = vec3(0.0f, 0.0f, 0.0f);
uniform vec3 u_cameraPos = vec3(0.0f, 0.0f, 0.0f);

void main()
{
	vec3 lightDirection = normalize(u_lightPos - FragPos);
	
	// Diffuse lighting
	float ambient  = 0.1f;
	float diffuse = max(dot(Normal, lightDirection), ambient);

	// Specular lighting
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(u_cameraPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float spec = pow(max(dot(viewDirection, reflectionDirection), ambient), 32);
	float specular = specularStrength * spec;  
	
	FragColor = texture(u_Texture, TexCoord) * vec4(Color, 1.0f) * (diffuse + specular) * vec4(u_lightColor, 1.0f);
}