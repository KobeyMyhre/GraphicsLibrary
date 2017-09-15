#version 450

layout(location = 0) in vec4 position;
layout(location = 0)uniform sampler2D terrain;

void main()
{
	vec2 texcoord = position.xy;
	float height = texture(terrain,texcoord).a;
	vec4 displaced = vec4(position.x,position.y, height, 1.0);

	gl_Position = displaced;
}