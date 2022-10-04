#pragma once

#include <GL\glew.h>

class Material
{
public:
	Material() = default;
	Material(GLfloat sIntensity, GLfloat shine);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	~Material();

private:
	GLfloat m_specularIntensity{};
	GLfloat m_shininess{};
};

