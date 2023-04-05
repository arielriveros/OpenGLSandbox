#pragma once
#include <glm/glm.hpp>
#include "Light.h"
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"

class PointLight : public Light
{
public:
	float Constant = 1.0f;
	float Linear = 0.7f;
	float Quadratic = 1.8f;

public:
	PointLight(std::string name, glm::vec3 color);
	~PointLight();
	void OnGui();
};