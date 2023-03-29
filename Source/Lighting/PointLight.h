#pragma once
#include <glm/glm.hpp>
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class PointLight
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Diffuse = glm::vec3(1.0f);
	glm::vec3 Ambient = glm::vec3(1.0f);
	glm::vec3 Specular = glm::vec3(1.0f);

	float Constant = 1.0f;
	float Linear = 0.7f;
	float Quadratic = 1.8f;

private:
	Sprite* m_Icon;

public:
	PointLight(glm::vec3 color);
	~PointLight();

	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetTransform() const;
	
};