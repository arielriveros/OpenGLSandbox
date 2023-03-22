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

vec4 pointLight()
{
	vec3 lightVec = u_lightPos - FragPos;
	float distance = length(lightVec);
	float a = 0.4;
	float b = 0.1;
	float intensity = 1.0f / ( a * distance + b * distance + 1.0f );


	vec3 lightDirection = normalize(lightVec);
	
	// Diffuse lighting
	float ambient  = 0.1f;
	float diffuse = max(dot(Normal, lightDirection), ambient) * intensity;

	// Specular lighting
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(u_cameraPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, Normal);
	float spec = pow(max(dot(viewDirection, reflectionDirection), ambient), 32);
	float specular = specularStrength * spec * intensity;  
	
	return texture(u_Texture, TexCoord) * vec4(Color, 1.0f) * (diffuse + specular) * vec4(u_lightColor, 1.0f);
}

void main()
{
	FragColor = pointLight();
}