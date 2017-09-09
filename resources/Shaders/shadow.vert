#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 UV;

layout(location = 0) uniform mat4 l_proj;
layout(location = 1) uniform mat4 l_view;
layout(location = 2) uniform mat4 model;

out vec4 vPos;
out vec2 vUV;
void main()
{
	vUV = UV;
	gl_Position = l_proj * l_view * model * position;
	vPos = model * position;
}
