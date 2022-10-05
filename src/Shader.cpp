#include "Shader.h"

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	m_shaderID = glCreateProgram();

	if (!m_shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(m_shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(m_shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(m_shaderID);
	glGetProgramiv(m_shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	m_uniformProjection									= GetUniformLocation("projection");
	m_uniformModel										= GetUniformLocation("model");
	m_uniformView										= GetUniformLocation("view");
	m_uniformEyePosition								= GetUniformLocation("eyePosition");
	m_uniformDirectionalLight.uniformAmbientIntensity	= GetUniformLocation("directionalLight.base.ambientIntensity");
	m_uniformDirectionalLight.uniformColour				= GetUniformLocation("directionalLight.base.colour");
	m_uniformDirectionalLight.uniformDiffuseIntensity	= GetUniformLocation("directionalLight.base.diffuseIntensity");
	m_uniformDirectionalLight.uniformDirection			= GetUniformLocation("directionalLight.direction");
	m_uniformSpecularIntensity							= GetUniformLocation("material.specularIntensity");
	m_uniformShininess									= GetUniformLocation("material.shininess");
	
	m_uniformPointLightCount							= GetUniformLocation("pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
		m_uniformPointLight[i].uniformColour = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		m_uniformPointLight[i].uniformAmbientIntensity = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		m_uniformPointLight[i].uniformDiffuseIntensity = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		m_uniformPointLight[i].uniformPosition = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		m_uniformPointLight[i].uniformConstant = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		m_uniformPointLight[i].uniformLinear = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		m_uniformPointLight[i].uniformExponent = GetUniformLocation(locBuff);
	}
}

GLuint Shader::GetProjectionLocation() const
{
	return m_uniformProjection;
}

GLuint Shader::GetModelLocation() const
{
	return m_uniformModel;
}

GLuint Shader::GetViewLocation() const
{
	return m_uniformView;
}

GLuint Shader::GetEyePositionLocation() const
{
	return m_uniformEyePosition;
}

GLuint Shader::GetAmbientIntensityLocation() const
{
	return m_uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColourLocation() const
{
	return m_uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetDiffuseIntensityLocation() const
{
	return m_uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation() const
{
	return m_uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation() const
{
	return m_uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation() const
{
	return m_uniformShininess;
}

GLuint Shader::GetUniformLocation(const char* uniform) const
{
	return glGetUniformLocation(m_shaderID, uniform);
}

GLuint Shader::GetAttributeLocation(const char* attribute) const
{
	return glGetAttribLocation(m_shaderID, attribute);
}

void Shader::SetDirectionalLight(const DirectionalLight* dLight)
{
	dLight->UseLight(m_uniformDirectionalLight.uniformAmbientIntensity, m_uniformDirectionalLight.uniformColour, m_uniformDirectionalLight.uniformDiffuseIntensity, m_uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(const PointLight* pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(m_uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; ++i)
	{
		pLight[i].UseLight(m_uniformPointLight[i].uniformAmbientIntensity, m_uniformPointLight[i].uniformColour,
			m_uniformPointLight[i].uniformDiffuseIntensity, m_uniformPointLight[i].uniformPosition, 
			m_uniformPointLight[i].uniformConstant, m_uniformPointLight[i].uniformLinear, m_uniformPointLight[i].uniformExponent);
	}

}

void Shader::UseShader()
{
	glUseProgram(m_shaderID);
}

void Shader::ClearShader()
{
	if (m_shaderID != 0)
	{
		glDeleteProgram(m_shaderID);
		m_shaderID = 0;
	}

	m_uniformProjection = 0;
	m_uniformModel = 0;
	m_uniformView = 0;
	m_uniformEyePosition = 0;
	m_uniformDirectionalLight.uniformAmbientIntensity	= 0;
	m_uniformDirectionalLight.uniformColour				= 0;
	m_uniformDirectionalLight.uniformDiffuseIntensity	= 0;
	m_uniformDirectionalLight.uniformDirection			= 0;
	m_uniformSpecularIntensity = 0;
	m_uniformShininess = 0;

}


void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader()
{
	ClearShader();
}
