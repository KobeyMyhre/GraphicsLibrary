#pragma once
#include "glm\glm.hpp"



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

struct Texture
{
	unsigned handle;
};

Texture makeTexture(unsigned w, unsigned h, unsigned c, const void  *pixels, bool isFloat = false);

void freeTexture(Texture &t);

struct FrameBufer
{
	unsigned handle;
	unsigned width, height;
	unsigned nTargets;
	Texture depthTarget;
	Texture targets[8];
};

FrameBufer MakeFrameBuffer(unsigned w, unsigned h, unsigned c, bool hasDepth, unsigned nTargets, unsigned nFloatTargets);
void freeFrameBuffer(FrameBufer &fb);


//class GameObject
//{
//public:
//	Geometry shape;
//	Texture skin;
//	glm::mat4 modelMatrix;
//
//};