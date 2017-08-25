#pragma once
		#version 450
		layout(location = 0) in vec4 position;
		layout(location = 1) in vec4 color;
		layout(location = 2) in vec2 UV;
		layout(location = 0) uniform float time; 
		layout(location = 1) uniform float press; 
		layout(location = 2) uniform float press1; 
		layout(location = 5) uniform mat4 rot; 
		out vec4 vPos;
		out vec2 vUV;
		 out vec4 vColor;
		void main ()
		{ 
		vPos = position;
		gl_Position = (position * rot);
		vUV = UV;
		gl_Position.x += press ; 
		gl_Position.y += press1  ; 
		vColor = vec4(sin((time + gl_Position.y) * 2),-cos((time + gl_Position.x) * 2), 0.1f,1); 
		};