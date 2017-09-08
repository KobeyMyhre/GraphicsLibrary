#include "GameObjects.h"
#include "graphics\draw.h"


void __internal::t_setUniforms(const Shader & s, int & loc_io, int & tex_io, const Camera & val)
{
	t_setUniforms(s, loc_io, tex_io, val.proj);
	t_setUniforms(s, loc_io, tex_io, val.view);
}

void __internal::t_setUniforms(const Shader & s, int & loc_io, int & tex_io, const SpecGloss & val)
{
	t_setUniforms(s, loc_io, tex_io, val.model); // 0 matrix
	t_setUniforms(s, loc_io, tex_io, val.diffuse); // 1 texture
	t_setUniforms(s, loc_io, tex_io, val.specular); // 2 texture
	t_setUniforms(s, loc_io, tex_io, val.normal); // 3 texture
	t_setUniforms(s, loc_io, tex_io, val.gloss); // 4 float
}


void  __internal::t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const DLite &val)
{
	t_setUniforms(s, loc_io, tex_io, val.getProj());
	t_setUniforms(s, loc_io, tex_io, val.getView());
	t_setUniforms(s, loc_io, tex_io, val.color);
	t_setUniforms(s, loc_io, tex_io, val.intensity);
	t_setUniforms(s, loc_io, tex_io, val.direction);
}
