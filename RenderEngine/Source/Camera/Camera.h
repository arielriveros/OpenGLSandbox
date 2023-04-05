#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera
{

public:
	glm::vec3 Position;
	glm::vec3 Forward		= glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up			= glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right			= glm::normalize(glm::cross(Forward, Up));

	float Yaw   = 0.0f;
	float Pitch = 0.0f;

	int m_Width, m_Height;
	float m_Fov, m_Near, m_Far;

	float speed = 0.05f;
	float sensitivity = 1.0f;

	Camera(int width, int height, glm::vec3 position, float fov = 45.0f, float near = 0.1f, float far = 100.0f);

	void Rotate(float deltaYaw, float deltaPitch);
	glm::mat4 GetViewProjectionMatrix() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

private:
	void updateCameraVectors();
};