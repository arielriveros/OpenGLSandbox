#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

struct Transform
{
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 EulerRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 GetMatrix() const
	{
		const glm::mat4 transMatrix = glm::translate(glm::mat4(1.0f), Position);

		const glm::mat4 rotX = glm::rotate(glm::mat4(1.0f),
			EulerRotation.x,
			glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 rotY = glm::rotate(glm::mat4(1.0f),
			EulerRotation.y,
			glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f),
			EulerRotation.z,
			glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4 rotationMatrix = rotY * rotX * rotZ;

		const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

		return transMatrix * rotationMatrix * scaleMatrix;
	}
};