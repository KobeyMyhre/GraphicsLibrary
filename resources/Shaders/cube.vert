#version 450

layout(location = 0) in vec4 position;

layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 norms;

layout(location = 0) uniform mat4 model;

out vec2 vUV;


out vec4 vMyPos;
void main()
{
	
	
	gl_Position = model * position;
	
	vUV = UV;
	
	
}