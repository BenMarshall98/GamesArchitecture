#version 430 core

in vec3 oNormal;
in vec3 oFragPos;

out vec4 oFragColor;

void main()
{
	vec3 lightDir = normalize(vec3(100.0f, 100.0f, 100.0f) - oFragPos);
	float diff = max(dot(oNormal, lightDir), 0.0f);
	
	oFragColor = vec4(diff, diff, diff, 1.0f);
}