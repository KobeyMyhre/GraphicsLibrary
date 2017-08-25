#version 450
in vec4 vCol;
in vec2 vUV;
layout(location = 1) uniform sampler2D map;
in vec4 vNorm;
out vec4 outColor;
void main()
{
outColor = texture(map,vUV.xy);
outColor = dot(-normalize(vec4(1,1,1,0)), vNorm) * outColor;
outColor.a = 1;
//outColor = texture(map,vUV.xy);
}