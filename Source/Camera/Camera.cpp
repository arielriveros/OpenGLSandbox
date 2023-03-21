#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float fov, float near, float far)
{
	m_Width = width;
	m_Height = height;
	m_Fov = fov;
	m_Near = near;
	m_Far = far;
	Position = position;
}

void Camera::Rotate(float deltaYaw, float deltaPitch)
{
	float xoffset = deltaYaw * sensitivity;
	float yoffset = deltaPitch * sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	updateCameraVectors();
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);

	view = glm::lookAt(Position, Position + Forward, Up);
	projection = glm::perspective(glm::radians(m_Fov), (float)(m_Width / m_Height), m_Near, m_Far);
	return projection * view;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Forward = glm::normalize(front);

	
	Right = glm::normalize(glm::cross(Forward, Up));
}
