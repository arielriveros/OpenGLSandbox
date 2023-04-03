#pragma once
#include <glm/glm.hpp>
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class DirectionalLight
{
public:
	glm::vec3 Position = glm::vec3(100.0f, 100.0f, 100.0f);

	glm::vec3 Diffuse = glm::vec3(1.0f);
	glm::vec3 Ambient = glm::vec3(0.2f);
	glm::vec3 Specular = glm::vec3(1.0f);


private:
	Sprite* m_Icon;
	float size = 25.0f;

public:
	DirectionalLight();
	~DirectionalLight();

	void Draw(const Camera& camera, const Shader& shader) const;

	glm::mat4 GetViewProjection() const
	{
		return glm::ortho(-size, size, -size, size, 0.1f, 10000.0f) * glm::lookAt(Position * size, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
};