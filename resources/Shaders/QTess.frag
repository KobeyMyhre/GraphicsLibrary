#version 450


out vec4 FragColor;
in vec3 gFacetNormal;
in vec3 gTriDistance;
in vec4 gPatchDistance;
layout(location = 4) uniform vec3 LightPosition;
layout(location = 5) uniform vec3 DiffuseMaterial;
layout(location = 6) uniform vec3 AmbientMaterial;
layout(location = 7) uniform vec3 SpecularMaterial;
layout(location = 8) uniform float Shininess;
const vec3 InnerLineColor = vec3(1, 1, 1);
const bool DrawLines = true;

 

float amplify(float d, float scale, float offset)
{
    d = scale * d + offset;
    d = clamp(d, 0, 1);
    d = 1 - exp2(-2*d*d);
    return d;
}

 

void main()

{
    vec3 N = normalize(gFacetNormal);
    vec3 L = LightPosition;
    vec3 E = vec3(0, 0, 1);
    vec3 H = normalize(L + E);

 

    float df = abs(dot(N, L));
    float sf = abs(dot(N, H));
    sf = pow(sf, Shininess);
    vec3 color = AmbientMaterial + df * DiffuseMaterial + sf * SpecularMaterial;
 

    if (DrawLines) 
	{
        float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
        float d2 = min(min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z), gPatchDistance.w);
        d1 = 1 - amplify(d1, 50, -0.5);
        d2 = amplify(d2, 50, -0.5);
        color = d2 * color + d1 * d2 * InnerLineColor;
    }

 
    FragColor = vec4(color, 1.0);

}