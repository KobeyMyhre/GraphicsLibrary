#pragma once
#include "glm/fwd.hpp"


struct Geometry;
struct Shader;
struct FrameBufer;
struct Texture;

void draw(const FrameBufer &f, const Shader &s, const Geometry &g);

void tess_draw(const FrameBufer &f, const Shader &s, const Geometry &g);

enum RenderFlag 
{
	NONE = 0,
	DEPTH = 1,
	ADDITIVE =2
};
void setFlags(int flags);


void setUniform(const Shader &shader, int location, float value);
void setUniform(const Shader &shader, int location, int value);
void setUniform(const Shader &shader, int location, double value);
void setUniform(const Shader &shader, int location, const Texture &value, int slot);

namespace __internal
{
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, float val);

	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, int val);
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const Texture &val);
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const glm::vec4 &val);
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const glm::vec3 &val);
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const glm::mat4 &val);
	void t_setUniforms(const Shader &s, int &loc_io, int &tex_io, const glm::mat3 &val);
}


template<typename T, typename ...U>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val, U &&...uniforms)
{
	__internal::t_setUniforms(s, loc_io, tex_io, val);
	setUniforms(s, loc_io, tex_io, uniforms...);
}
template<typename T>
void setUniforms(const Shader &s, int &loc_io, int &tex_io, const T &val)
{
	__internal::t_setUniforms(s, loc_io, tex_io, val);
	
}

void clearFrameBuffer(const FrameBufer &fb, bool color = true, bool depth = true);