#pragma once
#include <glm/glm.hpp>
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class DirectionalLight
{
public:
	glm::vec3 Direction = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Diffuse = glm::vec3(1.0f);
	glm::vec3 Ambient = glm::vec3(0.2f);
	glm::vec3 Specular = glm::vec3(1.0f);


private:
	Sprite* m_Icon;

public:
	DirectionalLight();
	~DirectionalLight();

	void Draw(const Camera& camera, const Shader& shader) const;
};