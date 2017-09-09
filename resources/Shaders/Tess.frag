#version 450

out vec4 FragColor;
in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in float gPrimitive;

layout(location = 4) uniform vec3 lightPosition;
layout(location = 5) uniform vec3 DiffuseMaterial;
layout(location = 6) uniform vec3 AmbientMaterial;

float amplify(float d, float scale, float offset)
{
	d = scale * d + offset;
	d = clamp(d,0,1);
	d = 1 - exp2(-2*d*d);
	return d;

}



void main()
{
	vec3 N = normalize(gFacetNormal);
	vec3 L = lightPosition;
	float df = abs(dot(N,L));
	vec3 color = AmbientMaterial + df * DiffuseMaterial;

	float d1 = min(min(gTriDistance.x,gTriDistance.y), gTriDistance.z);
	float d2 = min(min(gPatchDistance.x,gPatchDistance.y), gPatchDistance.z);

	color = amplify(d1,40,-.05) * amplify(d2,60,-0.5) * color;

	FragColor = vec4(color, 1.0);


}