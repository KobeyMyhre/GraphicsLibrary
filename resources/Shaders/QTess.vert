#version 450

layout(location = 0) in vec4 position;

out vec3 vPos;
//////



void main()
{
/////
	
	vPos = position.xyz; 
	
}