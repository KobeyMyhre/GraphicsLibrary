#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"

#include "GenSHape.h"
#include <iostream>
#include <random>




void main()
{
	int count;
	Context context;
	context.init(1200, 600);

	Vertex verts[4] =
	{
		{ { 0,0, 0, 1 },{ 1.0,0.0, 0.0, 1.0 }, {0,0} },
		{ { 1,0, 0, 1 },{ 0,1.0, 1.0, 1.0 }, {1,0} },
		{ { 0,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 }, {0,1} },
		{ { 1,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 }, {1,1} },





	};

	unsigned idxs[6] = {
		0,1,2,
		3,1,2
	};


	//Geometry g = makeGeometry(verts, 4, idxs, 6);
	Geometry g = makeNGon(12, .1f, .5f);
						//14
	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"layout(location = 2) in vec2 UV;\n"
		"layout(location = 0) uniform float time; \n"
		"layout(location = 1) uniform float press; \n"
		"layout(location = 2) uniform float press1; \n"
		"out vec4 vPos;\n"
		"out vec2 vUV;"
		" out vec4 vColor;\n"
		"void main ()\n"
		"{ \n"
		"vPos = position;\n"
		"gl_Position = position;\n"
		"vUV = UV;"
		/*"gl_Position.x += sin(time * (gl_Position.x /4)+ press) ; \n"
		"gl_Position.y -= cos(time * (gl_Position.y /4)+ press1)  ; \n"*/
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
	// outColor = vUV* sin(time + vPos.xy));
	Shader s = makeShader(vsource, fsource);

	FrameBufer f = { 0,800,600 };
								//33 130 40
	unsigned char pixels[] = { 33,130,40
								,256,256,256 };
	unsigned char PixelMask[] = { 0,0 };
	for (int i = 0; i < 2; i++)
	{
		
		PixelMask[i] = rand() % 256 + 1;
		
	}

	pixels[0] *= PixelMask[0];
	pixels[3] *= PixelMask[3];

	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_Amask = makeTexture(2, 1, 1, pixels);


	double x;
	double y;

	float xpos = 0; 
	float ypos = 0;
	while (context.step())
	{
		xpos += context.getKey('D')*.01;
		ypos += context.getKey('W')*.01;
		xpos -= context.getKey('A')*.01;
		ypos -= context.getKey('S')*.01;

		std::cout << xpos << " " << ypos << std::endl;

		clearFrameBuffer(f);
		context.getMousePosition(x,y);
		x = 2* (x / 800) - 1;
		y = 1- 2*(y / 600) ;
		//std::cout << "X: " << x << "Y: " << y << std::endl;
		setUniform(s, 0, (float)context.getTime());
		setUniform(s, 3,t_magyel, 0);
		setUniform(s, 4, t_Amask, 1);
		/*setUniform(s, 1, (float)x);
		setUniform(s, 2, (float)y);*/

		setUniform(s, 1, (float)xpos);
		setUniform(s, 2, (float)ypos);
		draw(f, s, g);


		const float *input = context.GetJoystickAxes(0, &count);
		for (int i = 0; i < count; i++)
		{
			std::cout << "Idx" << i << ": " << input[i] << std::endl;
		}
		
	}

	freeShader(s);

	context.Terminate();

}