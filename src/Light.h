#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light() = default;
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);

	~Light();

protected:
	glm::vec3 m_colour{glm::vec3(1.0f)};
	GLfloat m_ambientIntensity{ 1.0f };
	GLfloat m_diffuseIntensity{ 0.0f };
};

