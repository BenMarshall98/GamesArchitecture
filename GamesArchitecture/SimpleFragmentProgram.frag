#version 430 core

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

layout (binding = 2) uniform pointLightBuffer
{
	vec3 lightPosition;
	vec3 lightColour;
};

void main()
{
	vec3 lightDir = normalize(lightPosition - oFragPos);
	float diff = max(dot(oNormal, lightDir), 0.0f);
	
	oFragColor = vec4(diff * lightColour, 1.0f);
}