#pragma once
#include <glm/glm.hpp>
#include "../Sprite/Sprite.h"
#include "../../Camera/Camera.h"

class Light
{
public:
	std::string Name = "Light";

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 Diffuse = glm::vec3(1.0f);
	glm::vec3 Ambient = glm::vec3(1.0f);
	glm::vec3 Specular = glm::vec3(1.0f);

private:
	Sprite* m_Icon;

public:
	Light(std::string name, glm::vec3 color);
	~Light();

	void Draw(const Camera& camera, const Shader& shader) const;
	void OnGui();

	glm::mat4 GetTransform() const;
};