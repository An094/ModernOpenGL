#include "PointLight.h"



PointLight::PointLight() : Light()
{
	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_constant = 1.0f;
	m_linear = 0.0f;
	m_exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, 
						GLfloat aIntensity, GLfloat dIntensity, 
						GLfloat xPos, GLfloat yPos, GLfloat zPos, 
						GLfloat con, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity)
{
	m_position = glm::vec3(xPos, yPos, zPos);
	m_constant = con;
	m_linear = lin;
	m_exponent = exp;
}

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
							GLuint diffuseIntensityLocation, GLuint positionLocation,
							GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) const
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
	glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);

	glUniform3f(positionLocation, m_position.x, m_position.y, m_position.z);
	glUniform1f(constantLocation, m_constant);
	glUniform1f(linearLocation, m_linear);
	glUniform1f(exponentLocation, m_exponent);
}

PointLight::~PointLight()
{
}
