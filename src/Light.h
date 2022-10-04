#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light() = default;
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	~Light();
	
	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);


private:
	glm::vec3 m_colour{glm::vec3(1.0f)};
	GLfloat m_ambientIntensity{ 1.0f };

	glm::vec3 m_direction{ glm::vec3(0.0f, -1.0f, 0.0f) };
	GLfloat m_diffuseIntensity{ 0.0f };
};

