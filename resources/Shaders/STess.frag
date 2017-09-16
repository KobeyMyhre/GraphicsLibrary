#version 450

out vec4 FragColor;
in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in float gPrimitive;

const bool DrawLines = false;

//////
in vec2 GeovUV;



layout(location = 4) uniform vec3 lightPosition;
layout(location = 5) uniform sampler2D DiffuseTex;
layout(location = 6) uniform sampler2D AmbientTex;
							//vec3
float amplify(float d, float scale, float offset)
{
	d = scale * d + offset;
	d = clamp(d,0,1);
	d = 1 - exp2(-2*d*d);
	return d;

}



void main()
{
	/////////
												//gTriDistance.xy
	


	vec3 N = normalize(gFacetNormal);
	vec3 L = lightPosition;
	float df = abs(dot(N,L)) * 5;

	float d1 = min(min(gTriDistance.x,gTriDistance.y), gTriDistance.z);
	float d2 = min(min(gPatchDistance.x,gPatchDistance.y), gPatchDistance.z);
	

											//PATCHES
	vec3 DiffuseMaterial = texture(DiffuseTex, GeovUV).xyz;
	vec3 AmbientMaterial = texture(AmbientTex, GeovUV).xyz;
	vec3 color = AmbientMaterial + df * DiffuseMaterial;


	 

	
	
	
	

	if(DrawLines)
	{
	
	color = amplify(d1,40,-.05) * amplify(d2,60,-0.5) * color;
	}
	

	//Colors
	//color = amplify(d1,40,-.05) * amplify(d2,60,-0.5) * Colors;

	FragColor = vec4(color, 1.0);
	

}