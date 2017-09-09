#version 450

in vec2 vUV;

layout(location = 1) uniform mat4 view;

layout(location = 3) uniform mat4 lightProj;
layout(location = 4) uniform mat4 lightView;

layout(location = 5) uniform vec4 lightColor;
layout(location = 6) uniform float intensity;
layout(location = 7) uniform vec3 lightDir;
layout(location = 8) uniform sampler2D normalMap;
layout(location = 9) uniform sampler2D posMap;
layout(location = 10) uniform sampler2D shadowMap;
layout(location = 11) uniform sampler2D specularMap;
layout(location = 12) uniform float  gloss;
layout(location = 0) out vec4 outDiffuse;
layout(location = 1) out vec4 outSpecular;

uniform float shadowBias = 0.01;

// Simple matrix that converts from clip space (-1,1) to UV space (0,1)
uniform mat4 clipToUV = mat4(0.5f, 0.0f, 0.0f, 0.0f,
							 0.0f, 0.5f, 0.0f, 0.0f,
							 0.0f, 0.0f, 0.5f, 0.0f,
							 0.5f, 0.5f, 0.5f, 1.0f);

float ghetto_pcf(in sampler2D shadowmap, in vec4 shadowPosition, int iterations)
{
	vec2 sDim = textureSize(shadowmap,0).xy;
	float retval = 0;
	
	vec2 uv = shadowPosition.xy;
	float z = shadowPosition.z - 0.01;

	//	if(texture(shadowmap,sUV.xy).r  < sUV.z - shadowBias)
	for(int i = -iterations; i <= iterations; ++i)
	{		
		if(!(texture(shadowmap, uv + vec2(i,0)/sDim).r < z))
			retval++;

		if(!(texture(shadowmap, uv + vec2(0,i)/sDim).r < z))
			retval++;
	}

	return retval / (iterations*4.0);
}


float phong(in vec3 N,in vec3 L,in vec3 V, in float power)
{
	if(dot(N, -L) <= 0) return 0;
	vec3 R = reflect(-L,N);
	float base = max(0,dot(V,R));
	
	return pow(base,power);
}

void main()
{
	vec3 vPos = texture(posMap, vUV).xyz;
	//vec3 normal = texture(normalMap,vUV); //( vTBN *  (2 * texture(normalMap,vUV) - 1)).xyz;
	vec4 sUV = clipToUV * lightProj * lightView * inverse(view) * vec4(vPos,1);
	
	vec4 specular = texture(specularMap,vUV);
	//

	float visibility = 1;
	if(texture(shadowMap,sUV.xy).r  < sUV.z - shadowBias)
	{
		visibility = ghetto_pcf(shadowMap, sUV, 16);	
		
	}



	vec3 L = (view * inverse(lightView)[2]).xyz;
	vec3 N = texture(normalMap, vUV).xyz;

	float lamb = (max(0,dot(-L,N)));

	float spec = phong(N, L, normalize( vPos),gloss);

	vec4 outSpecular = specular * spec * lightColor * intensity;

	outDiffuse = lightColor * intensity * lamb * visibility + outSpecular;
	//outDiffuse = texture(shadowMap, sUV.xy)
}