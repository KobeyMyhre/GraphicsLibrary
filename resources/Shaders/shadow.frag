#version 450

out vec4 outColor;
in vec4 vPos;
void main() 
{
	outColor = vPos;
}