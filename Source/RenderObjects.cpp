#include "graphics\RenderObjects.h"
#include "glinc.h"
#include "graphics\Vertex.h"

#ifdef _DEBUG
#include <iostream>
#endif


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

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

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

void freeShader(Shader & s)
{
	glDeleteProgram(s.handle);
	s = { 0 };
}

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char * pixels)
{
	Texture retval = { 0 };

	GLenum f = 0;
	switch (c)
	{
	case 1: f = GL_RED; break;
	case 2: f = GL_RG; break;
	case 3: f = GL_RGB; break;
	case 4: f = GL_RGBA; break;
	}

	glGenTextures(1, &retval.handle);
	glBindTexture(GL_TEXTURE_2D, retval.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, f, GL_UNSIGNED_BYTE, pixels);
	

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
