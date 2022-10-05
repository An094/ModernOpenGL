#include "Light.h"

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
	: m_colour{glm::vec3(red, green, blue)}, m_ambientIntensity{ aIntensity }, m_diffuseIntensity{dIntensity}
{
}

Light::~Light()
{
}
