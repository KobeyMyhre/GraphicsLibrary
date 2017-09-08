#version 450


layout(location = 1) uniform mat4 view;
layout(location = 3) uniform sampler2D normalMap;
layout(location = 4) uniform sampler2D diffuseMap;
layout(location = 5) uniform sampler2D specularMap;
layout(location = 6) uniform float  gloss;

layout(location = 7) uniform vec3 L_data;
layout(location = 8) uniform vec4 L_Color;
layout(location = 9) uniform float L_intensity;
layout(location = 10) uniform vec4 L_ambient;
layout(location = 11) uniform int L_type;

layout(location = 0) out vec4 outFinal;
layout(location = 1) out vec4 ourDiffuse;
layout(location = 2) out vec4 outSpecualar;
layout(location = 3) out vec4 outNormal;

out vec4 outColor;
in vec3 vPos;
in mat4 vTBN;
in vec2 vUV;

float lamb(in vec3 N, in vec3 L)
{
	return  max(0,dot(N,-L));
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
	vec3 normal =( vTBN *  (2 * texture(normalMap,vUV) - 1)).xyz;
	vec4 diffuse = texture(diffuseMap,vUV);
	vec4 specular = texture(specularMap,vUV);
	//if(vPos.x < 0) normal = vTBN[2].xyz;

	vec3 lDir = L_data;
	if(L_type == 1)
	{
		lDir = normalize(vPos.xyz - L_data);
	}

	float lamb = lamb(normal, lDir);
	float ambi = 1;
	
	float spec = phong(normal, lDir, normalize(view[3].xyz - vPos),gloss);
	

	vec4 outAmbient = diffuse * ambi * L_ambient;
	vec4 outDiffuse = diffuse * lamb * L_Color * L_intensity;
	vec4 outSpecular = specular * spec * L_Color * L_intensity;

	//outNormal = vec4(normal,0);

	outColor = outAmbient + outDiffuse + outSpecular;
	//outColor = outSpecular;
	//outColor = vec4(normal,1);
	//outColor = texture(diffuseMap, vUV) * lamb + vec4(1,1,0,1) * phong;
}