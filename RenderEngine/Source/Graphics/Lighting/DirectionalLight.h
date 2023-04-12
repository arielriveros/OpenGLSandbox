#pragma once
#include "Light.h"
#include "../Sprite/Sprite.h"
#include "../../Camera/Camera.h"
#include <glm/glm.hpp>

class DirectionalLight: public Light
{
private:
	float size = 35.0f;

public:
	DirectionalLight(std::string name, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~DirectionalLight();
	void OnGui();

	glm::mat4 GetViewProjection() const
	{
		return glm::ortho(-size, size, -size, size, 0.1f, 10000.0f) * glm::lookAt(Position * size, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
};