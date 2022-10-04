#include "Camera.h"

Camera::Camera(const glm::vec3& startPosition, const glm::vec3& startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	m_position = startPosition;
	m_worldUp = startUp;
	m_yaw = startYaw;
	m_pitch = startPitch;
	m_front = glm::vec3(0.0f, 0.0f, -1.0f);

	m_moveSpeed = startMoveSpeed;
	m_turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = m_moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		m_position += m_front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		m_position -= m_front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		m_position -= m_right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		m_position += m_right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= m_turnSpeed;
	yChange *= m_turnSpeed;

	m_yaw += xChange;
	m_pitch += yChange;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}

	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::update()
{
	m_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

