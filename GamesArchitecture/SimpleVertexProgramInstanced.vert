#version 430 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in mat4 model;

layout (binding = 1) uniform cameraBuffer
{
	mat4 view;
	mat4 projection;
};

out vec3 oNormal;
out vec3 oFragPos;

void main()
{
	gl_Position = projection * view * model * vec4(vertex, 1.0f);
	oNormal = normal;
	oFragPos = (model * vec4(vertex, 1.0f)).xyz;
}