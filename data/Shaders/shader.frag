#version 330

in vec4 vCol;
in vec2 TexCoord;
in vec3 Normal;

out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionLight;

void main()
{
	vec4 ambientColour = vec4(directionLight.colour, 1.0f) * directionLight.ambientIntensity;
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionLight.direction)), 0.0f);
	vec4 diffuseColour = vec4(directionLight.colour, 1.0f) * directionLight.diffuseIntensity * diffuseFactor;
	colour = texture(theTexture, TexCoord) * (ambientColour  + diffuseColour) ;
}