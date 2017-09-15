#define GLM_FORCE_SWIZZLE
#include "graphics\RenderObjects.h"
#include "glinc.h"
#include "graphics\Vertex.h"

#ifdef _DEBUG
#include <iostream>
#endif

glm::vec4 calcTanget(const Vertex &v0, const Vertex &v1, const Vertex &v2)
{
	glm::vec4 p1 = v1.position - v0.position;
	glm::vec4 p2 = v2.position - v0.position;

	glm::vec2 t1 = v1.UV - v0.UV;
	glm::vec2 t2 = v2.UV - v0.UV;

	return glm::normalize((p1*t2.y - p2 * t1.y) / (t1.x*t2.y - t1.y*t2.x));
}


void solveTangets(Vertex * v, size_t vsize, const unsigned * idxs, size_t isize)
{
	for (int i = 0; i < isize; i += 3)
	{
		glm::vec4 T = calcTanget(v[idxs[i]], v[idxs[i+1]], v[idxs[i + 2]]);

		for (int j = 0; j < 3; j++)
		{
			v[idxs[i + j]].tangent = T + v[idxs[i + j]].tangent;
		}
	}

	for (int i = 0; i < vsize; i++)
	{
		v[i].bitangent = glm::vec4(glm::cross(v[i].norms.xyz(), v[i].tangent.xyz()), 0);
	}
}


Geometry makeGeometry(const Vertex * vertices, size_t vsize,
	const unsigned *idxs, size_t isize)
{
	Geometry retval = {0,0,0,isize};

	glGenBuffers(1, &retval.vbo);
	glGenBuffers(1, &retval.ibo);
	glGenVertexArrays(1, &retval.handle);

	glBindVertexArray(retval.handle);
	glBindBuffer(GL_ARRAY_BUFFER, retval.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo);

	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(unsigned), idxs, GL_STATIC_DRAW);
	
	
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)0 );
	
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16);

	glEnableVertexAttribArray(2);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);
	
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)40);

	glEnableVertexAttribArray(4);

	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)56);

	glEnableVertexAttribArray(5);

	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)72);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return retval;
}

void freeGeometry(Geometry & g)
{
	glDeleteBuffers(1, &g.vbo);
	glDeleteBuffers(1, &g.ibo);
	glDeleteVertexArrays(1, &g.handle);
	g = { 0,0,0,0 };
}



Shader makeShader(const char * vert_source, const char * rag_source)
{
	Shader retval = { 0 };

	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vert_source, 0);
	glShaderSource(fs, 1, &rag_source, 0);

	glCompileShader(vs);

#ifdef  _DEBUG
	GLint successVS = GL_FALSE;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &successVS);
	if (successVS == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

	glCompileShader(fs);

#ifdef  _DEBUG
	GLint successFS = GL_FALSE;

	glGetShaderiv(fs, GL_COMPILE_STATUS, &successFS);
	if (successFS == GL_FALSE)
	{
		int lengthz = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &lengthz);
		char *log = new char[lengthz];
		glGetShaderInfoLog(fs, lengthz, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG
	


	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);

	glLinkProgram(retval.handle);

#ifdef  _DEBUG
	GLint successRET = GL_FALSE;

	glGetProgramiv(retval.handle, GL_LINK_STATUS, &successRET);
	if (successRET == GL_FALSE)
	{
		int lengthx = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &lengthx);
		char *log = new char[lengthx];
		glGetProgramInfoLog(retval.handle, lengthx, 0, log);
		std::cerr << log << std::endl;
		delete [] log;
	}

#endif //  _DEBUG

	glDeleteShader(vs);
	glDeleteShader(fs);



	return retval;
}

Shader makeShader(const char * vert_source, const char * rag_source, const char * cntrl_source, const char * eval_source)
{
	Shader retval = { 0 };

	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned cl = glCreateShader(GL_TESS_CONTROL_SHADER);
	unsigned el = glCreateShader(GL_TESS_EVALUATION_SHADER);
	

	glShaderSource(vs, 1, &vert_source, 0);
	glShaderSource(fs, 1, &rag_source, 0);
	
	glShaderSource(cl, 1, &cntrl_source, 0);
	glShaderSource(el, 1, &eval_source, 0);
	//////VERTEX SHADER
	glCompileShader(vs);

#ifdef  _DEBUG
	GLint successVS = GL_FALSE;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &successVS);
	if (successVS == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

	//////FRAGMENT SHADER
	glCompileShader(fs);

#ifdef  _DEBUG
	GLint successFS = GL_FALSE;

	glGetShaderiv(fs, GL_COMPILE_STATUS, &successFS);
	if (successFS == GL_FALSE)
	{
		int lengthz = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &lengthz);
		char *log = new char[lengthz];
		glGetShaderInfoLog(fs, lengthz, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}


	//////VERTEX SHADER
	


#endif //  _DEBUG

	//////CONTROL SHADER
	glCompileShader(cl);

#ifdef  _DEBUG
	GLint successCL = GL_FALSE;

	glGetShaderiv(cl, GL_COMPILE_STATUS, &successCL);
	if (successCL == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(cl, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(cl, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

	//////EVALUATION SHADER
	glCompileShader(el);

#ifdef  _DEBUG
	GLint successEL = GL_FALSE;

	glGetShaderiv(el, GL_COMPILE_STATUS, &successEL);
	if (successEL == GL_FALSE)
	{
		int lengthz = 0;
		glGetShaderiv(el, GL_INFO_LOG_LENGTH, &lengthz);
		char *log = new char[lengthz];
		glGetShaderInfoLog(el, lengthz, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG


	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glAttachShader(retval.handle, cl);
	glAttachShader(retval.handle, el);
	

	glLinkProgram(retval.handle);

#ifdef  _DEBUG
	GLint successRET = GL_FALSE;

	glGetProgramiv(retval.handle, GL_LINK_STATUS, &successRET);
	if (successRET == GL_FALSE)
	{
		int lengthx = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &lengthx);
		char *log = new char[lengthx];
		glGetProgramInfoLog(retval.handle, lengthx, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(cl);
	glDeleteShader(el);


	return retval;
}

Shader makeShader(const char *vert_source, const char *rag_source, const char *geo_source, const char *cntrl_source, const char *eval_source)
{
	Shader retval = { 0 };

	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	unsigned cl = glCreateShader(GL_TESS_CONTROL_SHADER);
	unsigned el = glCreateShader(GL_TESS_EVALUATION_SHADER);
	unsigned geo = glCreateShader(GL_GEOMETRY_SHADER);

	glShaderSource(vs, 1, &vert_source, 0);
	glShaderSource(fs, 1, &rag_source, 0);
	glShaderSource(geo, 1, &geo_source, 0);
	glShaderSource(cl, 1, &cntrl_source, 0);
	glShaderSource(el, 1, &eval_source, 0);
//////VERTEX SHADER
	glCompileShader(vs);

#ifdef  _DEBUG
	GLint successVS = GL_FALSE;

	glGetShaderiv(vs, GL_COMPILE_STATUS, &successVS);
	if (successVS == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(vs, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

//////FRAGMENT SHADER
	glCompileShader(fs);

#ifdef  _DEBUG
	GLint successFS = GL_FALSE;

	glGetShaderiv(fs, GL_COMPILE_STATUS, &successFS);
	if (successFS == GL_FALSE)
	{
		int lengthz = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &lengthz);
		char *log = new char[lengthz];
		glGetShaderInfoLog(fs, lengthz, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}


	//////VERTEX SHADER
	glCompileShader(geo);

#ifdef  _DEBUG
	GLint successGEO = GL_FALSE;

	glGetShaderiv(geo, GL_COMPILE_STATUS, &successGEO);
	if (successGEO == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(geo, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(geo, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG



#endif //  _DEBUG

//////CONTROL SHADER
	glCompileShader(cl);

#ifdef  _DEBUG
	GLint successCL = GL_FALSE;

	glGetShaderiv(cl, GL_COMPILE_STATUS, &successCL);
	if (successCL == GL_FALSE)
	{
		int length = 0;
		glGetShaderiv(cl, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(cl, length, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

//////EVALUATION SHADER
	glCompileShader(el);

#ifdef  _DEBUG
	GLint successEL = GL_FALSE;

	glGetShaderiv(el, GL_COMPILE_STATUS, &successEL);
	if (successEL == GL_FALSE)
	{
		int lengthz = 0;
		glGetShaderiv(el, GL_INFO_LOG_LENGTH, &lengthz);
		char *log = new char[lengthz];
		glGetShaderInfoLog(el, lengthz, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG


	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glAttachShader(retval.handle, cl);
	glAttachShader(retval.handle, el);
	glAttachShader(retval.handle, geo);

	glLinkProgram(retval.handle);

#ifdef  _DEBUG
	GLint successRET = GL_FALSE;

	glGetProgramiv(retval.handle, GL_LINK_STATUS, &successRET);
	if (successRET == GL_FALSE)
	{
		int lengthx = 0;
		glGetProgramiv(retval.handle, GL_INFO_LOG_LENGTH, &lengthx);
		char *log = new char[lengthx];
		glGetProgramInfoLog(retval.handle, lengthx, 0, log);
		std::cerr << log << std::endl;
		delete[] log;
	}

#endif //  _DEBUG

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(geo);
	glDeleteShader(cl);
	glDeleteShader(el);


	return retval;
}

void freeShader(Shader & s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}

Texture makeTexture(unsigned w, unsigned h, unsigned c, const void * pixels, bool isFloat)
{
	Texture retval = { 0 };

	GLenum f = 0;
	GLenum i = 0;
	switch (c)
	{
	case 0: f = GL_DEPTH_COMPONENT; i = GL_DEPTH24_STENCIL8; break;
	case 1: f = GL_RED;  i = isFloat ? GL_R32F		: GL_RED; break;
	case 2: f = GL_RG; i = isFloat ? GL_RG32F		: GL_RG; break;
	case 3: f = GL_RGB; i = isFloat ? GL_RGB32F		: GL_RGB; break;
	case 4: f = GL_RGBA; i = isFloat ? GL_RGBA32F	: GL_RGBA; break;
	}

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, ((isFloat || c== 0)? i : f), w, h, 0, f, isFloat ? GL_FLOAT : GL_UNSIGNED_BYTE, pixels);
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	return retval;
}

void freeTexture(Texture & t)
{
	glDeleteTextures(1, &t.handle);
	t = { 0 };
}

FrameBufer MakeFrameBuffer(unsigned w, unsigned h, unsigned c, bool hasDepth, unsigned nTargets, unsigned nFloatTargets)
{
	FrameBufer retval = { 0,w,h,0,0,{0} };

	retval.nTargets = nTargets + nFloatTargets;

	glGenFramebuffers(1, &retval.handle);
	glBindFramebuffer(GL_FRAMEBUFFER, retval.handle);

	if (hasDepth)
	{
		retval.depthTarget = makeTexture(w, h, 0, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retval.depthTarget.handle, 0);
	}

	

	const GLenum attachments[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };

	for (int i = 0; i < retval.nTargets && i < 8; ++i)
	{
		retval.targets[i] = makeTexture(w, h, c, 0, i >= nTargets);
		glFramebufferTexture(GL_FRAMEBUFFER, attachments[i], retval.targets[i].handle, 0);
	}

	glDrawBuffers(retval.nTargets, attachments);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	return retval;
}

void freeFrameBuffer(FrameBufer & fb)
{
	for (unsigned i = 0; i < fb.nTargets; ++i)
		freeTexture(fb.targets[i]);

	glDeleteFramebuffers(1, &fb.handle);
	fb = { 0,0,0,0 };

}
