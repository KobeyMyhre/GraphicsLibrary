#version 450

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 norm;

layout(location = 0) uniform mat4 model;
layout(location = 2) uniform float time;

out vec2 vUV;
out vec4 vCol;
out vec4 vNorm;

out vec4 vPos;
void main()
{
	
	vNorm = model * norm;
	gl_Position = model * pos ;
	gl_Position.x += (sin(time) / 1.5 );
	gl_Position.z += (cos(time) / 1.5);
	vPos = pos;
	vUV = UV;
	
	vCol = col;
}
