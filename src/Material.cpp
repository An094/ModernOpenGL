#include "Material.h"


Material::Material(GLfloat sIntensity, GLfloat shine)
	: m_specularIntensity{sIntensity}, m_shininess{shine}
{
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, m_specularIntensity);
	glUniform1f(shininessLocation, m_shininess);
}

Material::~Material()
{
}
