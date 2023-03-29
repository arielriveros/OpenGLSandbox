#version 330 core

in vec2 TexCoord;
in mat3 TBN;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_cameraPos = vec3(0.0f, 0.0f, 0.0f);

struct Material {
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material u_material;

uniform bool u_noTex;
uniform bool u_noNormalMap;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;
uniform sampler2D texture_normal0;

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

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
    // ambient
    vec3 ambient = light.ambient * diffuseMap;

    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseMap;

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess * 128.0);
    vec3 specular = light.specular * spec * specularMap;
    // combine results

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseMap, vec3 specularMap)
{
    vec3 lightVec = light.position - fragPos;
    float distance = length(lightVec);
    float pointIntensity = 1.0f / ( light.linear * distance + light.quadratic * distance * distance + light.constant );

	// ambient
    vec3 ambient = light.ambient * diffuseMap;

    // diffuse 
    vec3 lightDir = normalize(lightVec);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseMap;

    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), u_material.shininess * 128.0);
    vec3 specular = light.specular * spec * specularMap;

    return (ambient + diffuse + specular) * pointIntensity;
}

void main()
{
    vec3 normal = TBN[2];
    if(!u_noNormalMap)
    {
        normal = texture(texture_normal0, TexCoord).rgb;
        normal = normalize(normal * 2.0 - 1.0);
        normal = TBN * normal;
    }

    vec3 diffuseMap;
    vec3 specularMap;

    if(u_noTex)
    {
        diffuseMap = u_material.diffuse;
        specularMap = u_material.specular;
    }
    else
    {
        vec4 texColor = texture(texture_diffuse0, TexCoord);
        if(texColor.a < 0.2)
        {
            discard;
        }
        diffuseMap = texColor.rgb;
        specularMap = texture(texture_specular0, TexCoord).rgb;
    }

    vec3 viewDir = normalize(u_cameraPos - FragPos);

    vec3 result = vec3(0.0);

    result += CalcDirLight(u_directionalLight, normal, viewDir, diffuseMap, specularMap);
    for(int i=0; i < u_pointLightsCount; i++)
        result += CalcPointLight(u_pointLights[i], normal, FragPos, viewDir, diffuseMap, specularMap);

    FragColor = vec4(result, 1.0);
}