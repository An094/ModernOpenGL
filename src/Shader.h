#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>

class Shader
{
public:
	Shader() = default;
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() const;
	GLuint GetModelLocation() const;
	GLuint GetViewLocation() const;
	GLuint GetEyePositionLocation() const;
	GLuint GetAmbientIntensityLocation() const;
	GLuint GetAmbientColourLocation() const;
	GLuint GetDiffuseIntensityLocation() const;
	GLuint GetDirectionLocation() const;
	GLuint GetSpecularIntensityLocation() const;
	GLuint GetShininessLocation() const;

	GLuint GetUniformLocation(const char* uniform) const;
	GLuint GetAttributeLocation(const char* attribute) const;

	void UseShader();
	void ClearShader();


private:
	GLuint m_shaderID{}, m_uniformProjection{}, m_uniformModel{}, m_uniformView{}, m_uniformEyePosition{},
		m_uniformAmbientIntensity{}, m_uniformAmbientColour{}, 
		m_uniformDiffuseIntensity{}, m_uniformDirection{}, m_uniformSpecularIntensity{}, m_uniformShininess;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

