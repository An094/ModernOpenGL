#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Constant.h"
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

	void SetDirectionalLight(const DirectionalLight* dLight);
	void SetPointLights(const PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(const SpotLight* sLight, unsigned int sLightCount);

	void UseShader();
	void ClearShader();


private:
	GLuint m_shaderID{}, m_uniformProjection{}, m_uniformModel{}, m_uniformView{}, m_uniformEyePosition{},
		m_uniformSpecularIntensity{}, m_uniformShininess{};
	int pointLightCount{};
	int spotLightCount{};
	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformDirection;
	} m_uniformDirectionalLight;

	GLuint m_uniformPointLightCount;

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} m_uniformPointLight[MAX_POINT_LIGHTS];

	GLuint m_uniformSpotLightCount;

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;
		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
		GLuint uniformDirection;
		GLuint uniformEdge;
	} m_uniformSpotLight[MAX_SPOT_LIGHTS];

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

