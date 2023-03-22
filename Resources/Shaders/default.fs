#version 330 core

in vec2 TexCoord;
in vec3 Normal;  
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 u_cameraPos = vec3(0.0f, 0.0f, 0.0f);

struct Material {
    sampler2D albedoTexture;
    vec3 albedo;
    vec3 specular;
    float shininess;
}; 

uniform Material u_material;

struct PointLight {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform PointLight u_pointLight;  

void main()
{
    vec3 normal = Normal;

    vec3 lightVec = u_pointLight.position - FragPos;
    float distance = length(lightVec);
    float pointIntensity = 1.0f / ( u_pointLight.linear * distance + u_pointLight.quadratic * distance + u_pointLight.constant );

	// ambient
    vec3 ambient = u_pointLight.ambient * u_material.albedo * vec3(texture(u_material.albedoTexture, TexCoord));

    // diffuse 
    vec3 lightDir = normalize(u_pointLight.position - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = u_pointLight.diffuse * diff * vec3(texture(u_material.albedoTexture, TexCoord)) * u_material.albedo;

    // specular
    vec3 viewDir = normalize(u_cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = u_pointLight.specular * spec * u_material.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * pointIntensity, 1.0);
}