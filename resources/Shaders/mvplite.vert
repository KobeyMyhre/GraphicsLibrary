#version 450

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in vec4 normal;

layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;
out vec4 vNormal;
out vec2 vUV;

void main()
{
    gl_Position = proj * view * model * position;
    vNormal = model *normal;
	vUV = texcoord;
	
}