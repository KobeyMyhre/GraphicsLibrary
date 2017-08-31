#pragma once
struct Vertex;
struct Geometry
{
	unsigned handle, // vertex array object 
			vbo,	 // vertex buffer
			ibo,	 // index buffer
			size;	 // how many indices make up this model

};


Geometry makeGeometry(const Vertex * vertices, size_t vsize, 
						const unsigned *idxs, size_t isize);

void freeGeometry(Geometry &g);

void solveTangets(Vertex *v, size_t vsize,
	const unsigned *idxs, size_t isize);

struct Shader
{
	unsigned handle;
};

Shader makeShader(const char *vert_source, const char *rag_source);

void freeShader(Shader &s);

struct FrameBufer
{
	unsigned handle;
	unsigned width, height;
};

struct Texture
{
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c, const unsigned char *pixels);

void freeTexture(Texture &t);

