#version 330 core

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_cameraPos = vec3(0.0f, 0.0f, 0.0f);

struct Material {
    sampler2D albedoTexture;
    sampler2D specularTexture;

    vec3 albedo;
    vec3 specular;

    float shininess;
}; 

uniform Material u_material;

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform DirectionalLight u_directionalLight;

#define MAX_LIGHTS 4
uniform int u_pointLightsCount = 0;
uniform PointLight u_pointLights[MAX_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.ambient * u_material.albedo * vec3(texture(u_material.albedoTexture, TexCoord));

    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.albedoTexture, TexCoord)) * u_material.albedo;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specularTexture, TexCoord)) * u_material.specular;
    // combine results

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightVec = light.position - fragPos;
    float distance = length(lightVec);
    float pointIntensity = 1.0f / ( light.linear * distance + light.quadratic * distance * distance + light.constant );

	// ambient
    vec3 ambient = light.ambient * u_material.albedo * vec3(texture(u_material.albedoTexture, TexCoord));

    // diffuse 
    vec3 lightDir = normalize(lightVec);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_material.albedoTexture, TexCoord)) * u_material.albedo;

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), u_material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_material.specularTexture, TexCoord)) * u_material.specular;

    return (ambient + diffuse + specular) * pointIntensity;
}

void main()
{
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(u_cameraPos - FragPos);

    vec3 result = vec3(0.0f);

    result += CalcDirLight(u_directionalLight, normal, viewDir);
    for(int i=0; i < u_pointLightsCount; i++)
        result += CalcPointLight(u_pointLights[i], normal, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}