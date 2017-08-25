#pragma once
	#version 450
		in vec4 vPos;
		in vec2 vUV;
		layout(location = 0) uniform float time; 
		 in vec4 vColor;
		out vec4 outColor;
		layout(location = 3) uniform sampler2D map;
		layout(location = 4) uniform sampler2D mask;
		void main () { outColor = texture(map,vUV * sin(time)) * texture(mask, vUV).rrrr; };