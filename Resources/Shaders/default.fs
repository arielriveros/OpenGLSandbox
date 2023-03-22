#version 330 core

in vec3 Color;
in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_cameraPos = vec3(0.0f, 0.0f, 0.0f);

struct Material {
    sampler2D albedo;
    vec3 ambient;
    vec3 specular;
    float shininess;
}; 

uniform Material u_material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_light;  

float calculatePointLightIntensity(float a, float b)
{
    // Point intensity
    vec3 lightVec = u_light.position - FragPos;
    float distance = length(lightVec);
    return 1.0f / ( a * distance + b * distance + 1.0f );
}

void main()
{
    float pointIntensity = calculatePointLightIntensity(3.0, 0.4);

	// ambient
    vec3 ambient = u_light.ambient * u_material.ambient;

    // diffuse 
    vec3 lightDir = normalize(u_light.position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = u_light.diffuse * diff * vec3(texture(u_material.albedo, TexCoord));

    // specular
    vec3 viewDir = normalize(u_cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_light.specular * (spec * u_material.specular);  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * pointIntensity, 1.0);
}