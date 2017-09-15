#version 450

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec4 norms;
layout(location = 4) in vec4 tangent;
layout(location = 5) in vec4 bitangent;



out VS_OUT{
	vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
}vs_out;



layout(location = 0)uniform mat4 projection;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform vec3 lightPos;
layout(location = 4)uniform vec3 viewPos;

//////



void main()
{
/////
	
	vPos = position.xyz; 
	


	 gl_Position      = projection * view * model * vec4(vPos, 1.0);
    vs_out.FragPos   = vec3(model * vec4(vPos, 1.0));   
    vs_out.TexCoords = UV;    
    
    vec3 T   = normalize(mat3(model) * tangent);
    vec3 B   = normalize(mat3(model) * bitangent);
    vec3 N   = normalize(mat3(model) * norms);
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.TangentLightPos = TBN * lightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;

}