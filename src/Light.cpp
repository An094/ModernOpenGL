#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
	: m_colour{glm::vec3(red, green, blue)}, m_ambientIntensity{ aIntensity }, m_direction{glm::vec3(xDir, yDir, zDir)}, m_diffuseIntensity{dIntensity}
{
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
	glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);
}

Light::~Light()
{
}
