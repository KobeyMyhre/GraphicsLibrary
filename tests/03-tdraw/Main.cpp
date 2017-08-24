#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"

#include "GenSHape.h"
#include <iostream>
#include <random>

#include "glm\glm.hpp"
#include "glm\ext.hpp"


void main()
{
	int count;
	Context context;
	context.init(1200, 600);

	Vertex verts[4] =
	{
		{ { 0,0, 0, 1 },{ 1.0,0.0, 0.0, 1.0 },{ 0,0 } },
		{ { 1,0, 0, 1 },{ 0,1.0, 1.0, 1.0 },{ 1,0 } },
		{ { 0,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 },{ 0,1 } },
		{ { 1,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 },{ 1,1 } },





	};

	unsigned idxs[6] = {
		0,1,2,
		3,1,2
	};


	//Geometry g = makeGeometry(verts, 4, idxs, 6);
	Geometry g = makeNGon(12, .1f, .2f);
	Geometry g1 = makeNGon(6, .1f, .15f);
	//14
	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 UV;\n"
		"layout(location = 0) uniform float time; \n"
		"layout(location = 1) uniform float press; \n"
		"layout(location = 2) uniform float press1; \n"
		"layout(location = 5) uniform mat4 rot; \n"
		"out vec4 vPos;\n"
		"out vec2 vUV;"
		" out vec4 vColor;\n"
		"void main ()\n"
		"{ \n"
		"vPos = position;\n"
		"gl_Position = (position * rot);\n"
		"vUV = UV;"
		"gl_Position.x += press ; \n"
		"gl_Position.y += press1  ; \n"
		"vColor = vec4(sin((time + gl_Position.y) * 2),-cos((time + gl_Position.x) * 2), 0.1f,1); "
		"}\n";
	//
	const char* fsource =
		"#version 450\n"
		"in vec4 vPos;\n"
		"in vec2 vUV;"
		"layout(location = 0) uniform float time; \n"
		" in vec4 vColor;\n"
		"out vec4 outColor;\n"
		"layout(location = 3) uniform sampler2D map;"
		"layout(location = 4) uniform sampler2D mask;"
		"void main () { outColor = texture(map,vUV * sin(time)) * texture(mask, vUV).rrrr; }\n";

	//UV * sin(time)
	//outColor = vColor
	// outColor = vUV* sin(time + vPos.xy));	"gl_Position = trans * position;\n"

	//(position * rot ) 

	const char* vsource2 =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 UV;\n"
		"layout(location = 0) uniform vec4 stuff; \n"
		"layout(location = 3) uniform mat4 rot; \n"
		"layout(location = 4) uniform mat4 trans; \n"
		"layout(location = 5) uniform float time; \n"
		"out vec4 vPos;\n"
		"out vec2 vUV;"
		" out vec4 vColor;\n"
		"void main ()\n"
		"{ \n"
		"vPos = position;\n"
		"gl_Position = position;"
		"gl_Position.x +=  sin(time) /3;\n"
		"gl_Position.y +=  cos(time) /2;\n"
		"vUV = UV;"
		" \n"
		" \n"
		"vColor = stuff; "
		"}\n";
	//
	const char* fsource2 =
		"#version 450\n"
		"in vec4 vPos;\n"
		"in vec2 vUV;"
		"layout(location = 5) uniform float time; \n"
		" \n"
		" in vec4 vColor;\n"
		"out vec4 outColor;\n"
		"layout(location = 1) uniform sampler2D map;"
		"layout(location = 2) uniform sampler2D mask;"
		"void main () { outColor = vec4(sin(time /3), sin(time),sin(time / 7),0); }\n";



	Shader s = makeShader(vsource, fsource);
	Shader s2 = makeShader(vsource2, fsource2);
	FrameBufer f = { 0,800,600 };
	//33 130 40
	unsigned char pixels[] = { 33,200,40
		,150,150,200 };
	unsigned char PixelMask[] = { 0,0 };
	for (int i = 0; i < 2; i++)
	{

		PixelMask[i] = rand() % 256 + 1;

	}

	pixels[0] *= PixelMask[0];
	pixels[3] *= PixelMask[3];

	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_Amask = makeTexture(2, 1, 2, pixels);


	double x;
	double y;

	glm::vec4 nippz;
	



	float xpos = 0;
	float ypos = 0;
	while (context.step())
	{
		int loc = 0;
		int tslot = 0;

		int loc2 = 0;
		int tslot2 = 0;

		xpos += context.getKey('D')*.01;
		ypos += context.getKey('W')*.01;
		xpos -= context.getKey('A')*.01;
		ypos -= context.getKey('S')*.01;

		int one = context.getKey('R');
		int two = context.getKey('G');
		int three = context.getKey('B');

		three = 1;

		nippz.x = one;
		nippz.y = two;
		nippz.z = three;
		
		glm::mat4 Rotatematrix = glm::rotate((float)context.getTime(), glm::vec3(.5f, 1.f, 0.5f));
		glm::mat4 TranslateMatrix = glm::translate(glm::vec3(0, .5f, 0));

		//std::cout << xpos << " " << ypos << std::endl;

		//clearFrameBuffer(f);



		context.getMousePosition(x, y);
		x = 2 * (x / 800) - 1;
		y = 1 - 2 * (y / 600);
		//std::cout << "X: " << x << "Y: " << y << std::endl;
		

		setUniforms(s, loc, tslot, (float)context.getTime(),xpos,ypos, t_magyel, t_Amask, Rotatematrix);
		setUniforms(s2, loc2, tslot2, nippz, t_magyel, t_Amask, Rotatematrix, TranslateMatrix, (float)context.getTime());
		//setUniform(s, 0, (float)context.getTime());
		//setUniform(s, 3, t_magyel, 0);
		//setUniform(s, 4, t_Amask, 1);
		///*setUniform(s, 1, (float)x);
		//setUniform(s, 2, (float)y);*/

		//setUniform(s, 1, (float)xpos);
		//setUniform(s, 2, (float)ypos);
		draw(f, s, g);
		draw(f, s2, g1);


	/*	const float *input = context.GetJoystickAxes(0, &count);
		for (int i = 0; i < count; i++)
		{
			std::cout << "Idx" << i << ": " << input[i] << std::endl;
		}*/

	}

	
	freeTexture(t_magyel);
	freeTexture(t_Amask);
	freeShader(s);
	context.Terminate();

}