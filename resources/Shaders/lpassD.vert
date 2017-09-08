#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 norms;
layout(location = 4) in vec4 tangent;
layout(location = 5) in vec4 bitangent;


layout(location = 0) uniform mat4 proj;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 model;


out vec2 vUV;
out vec4 vPos;
out mat4 vTBN;
void main()
{
	vUV = UV;
	vPos = position;
	vTBN = model * mat4(tangent, bitangent, norms, vec4(0,0,0,0));
	gl_Position = position;
}