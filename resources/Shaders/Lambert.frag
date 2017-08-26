#version 450

in vec2 vUV;
in vec3 vNormal;
layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec3 lightDir;
layout (location = 5) uniform vec4 lightCol;
out vec4 outColor;

void main()
{
	vec4 surfaceColor = texture(diffuse, vUV);
	float lambertianFactor = max(dot(vNormal, -lightDir),0);
	vec4 lambertianTerm = surfaceColor * lambertianFactor * lightCol;


    outColor = lambertianTerm;
	
}