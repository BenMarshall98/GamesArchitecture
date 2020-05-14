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

	if (mod(floor(oFragPos.x * 10.0f) + floor(oFragPos.z * 10.0f), 2) != 0.0f)
	{
		diff *= 0.5f;
	}
	
	oFragColor = vec4(diff * lightColour, 1.0f);
}