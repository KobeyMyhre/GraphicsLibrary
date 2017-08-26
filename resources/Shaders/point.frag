#version 450

in vec2 vUV;
in vec3 vNormal;
layout (location = 3) uniform sampler2D diffuse;
layout (location = 4) uniform vec4 lightPos;
layout (location = 5) uniform vec4 lightCol;
out vec4 outColor;
in vec4 vpos;
void main()
{
	vec3 DISP = (vpos - lightPos).xyz;
	vec4 surfaceColor = texture(diffuse, vUV);
	float dist = length(DISP);
	vec3 Dir = normalize(DISP);
	float lambertianFactor = max(dot(vNormal, -Dir),0);
	//lambertianFactor *= 1/(dist * dist);

	vec4 lambertianTerm = surfaceColor * lambertianFactor * lightCol + surfaceColor*.8;


    outColor = lambertianTerm;
	
}