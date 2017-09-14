#version 450

layout(location = 3)uniform mat4 ModelView;
layout(location = 7)uniform mat3 NormalMatrix;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 tePosition[3];
in vec3 tePatchDistance[3];
out vec3 gFacetNormal;
out vec3 gPatchDistance;
out vec3 gTriDistance;


//////////
in vec2 EvalvUV[3];
out vec2 GeovUV;


void main()
{
	
	vec3 A = tePosition[2] - tePosition[0];
	vec3 B = tePosition[1] - tePosition[0];

	vec2 a = EvalvUV[1] - EvalvUV[2] - EvalvUV[0];
	
	//GeovUV = a;
	GeovUV = EvalvUV[0];
	

	gFacetNormal = NormalMatrix * normalize(cross(A,B));

	gPatchDistance = tePatchDistance[0];
	gTriDistance = vec3(1,0,0);
	gl_Position = gl_in[0].gl_Position; EmitVertex();

	gPatchDistance = tePatchDistance[1];
	gTriDistance = vec3(0,1,0);
	gl_Position = gl_in[1].gl_Position; EmitVertex();

	gPatchDistance = tePatchDistance[2];
	gTriDistance = vec3(0,0,1);
	gl_Position = gl_in[2].gl_Position; EmitVertex();


	EndPrimitive();

}