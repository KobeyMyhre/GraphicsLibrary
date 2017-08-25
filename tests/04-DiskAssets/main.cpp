#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"

#include "GenSHape.h"
#include <iostream>
#include <random>
#include "graphics\Load.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"


void main()
{
	int count;
	Context context;
	context.init(800, 600);

	Vertex verts[4] =
	{
		{ { 0,0, 0, 1 },{ 1.0,0.0, 0.0, 1.0 },{ 0,0 } }, // 0
		{ { 1,0, 0, 1 },{ 0,1.0, 1.0, 1.0 },{ 1,0 } },	// 1
		{ { 0,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 },{ 0,1 } }, // 2 
		{ { 1,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 },{ 1,1 } }, // 3





	};

	unsigned idxs[6] = {
		0,1,2,
		3,1,2
	};

	Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	Geometry g3 = makeGeometry(verts, 4, idxs, 6);
	Geometry g = makeNGon(12, .1f, .2f);
	Geometry g1 = makeNGon(6, .1f, .15f);

	bool colorThing =true;
	bool DepthThing =true;
	

	
	//Shader s2 = makeShader(vsource2, fsource2);
	//Shader s2 = loadShader("../../resources/Shaders/test.vert", "../../resources/Shaders/test.frag");
	Shader scube = loadShader("../../resources/Shaders/Planet.vert", "../../resources/Shaders/Planet.frag");
	Shader ssphere = loadShader("../../resources/Shaders/cube.vert", "../../resources/Shaders/cube.frag");

	FrameBufer f = { 0,800,600 };
	//33 130 40
	unsigned char pixels[] = { 150,200,40
		,150,150,200 };
	

	Texture t_magyel = makeTexture(2, 1, 3, pixels);
	Texture t_Amask = makeTexture(2, 1, 2, pixels);

	Texture tex = loadTexture("../../resources/textures/Pink2.png");
	Texture planet = loadTexture("../../resources/textures/Color.jpg");


	int r = 4;
	int c = 2;
	int rows =4;
	int columns =4;


	float xpos = 0;
	float ypos = 0;
	int idx = 0;
	while (context.step())
	{
		glm::vec4 sunPos = {0,0,0,1};
		int loc = 0;
		int tslot = 0;

		int loc2 = 0;
		int tslot2 = 0;

	/*	xpos += context.getKey('D')*.01;
		ypos += context.getKey('W')*.01;
		xpos -= context.getKey('A')*.01;
		ypos -= context.getKey('S')*.01;*/

		xpos = context.getKey('S');
		ypos = context.getKey('W');

		if (xpos == 1)
		{
			idx = 4;
		}
		else if (ypos == 1)
		{
			idx = 12;
		}
		else
		{
			idx = 0;
		}


		

		glm::mat4 Rotatematrix = glm::rotate((float)context.getTime(), glm::vec3(0.f, 1.f, 0.5f))
									* glm::scale(glm::vec3(.75f,.75f,.75f));
		glm::mat4 TranslateMatrix = glm::scale(glm::vec3(.25f, .25f, .25f)) * glm::rotate((float)context.getTime(), glm::vec3(-1.f, .5f, -.25f));

	
		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(f,colorThing,DepthThing);



		//setUniforms(s, loc, tslot, (float)context.getTime(), xpos, ypos, t_magyel, t_Amask, Rotatematrix);
		//draw(f, s, g);
		//setUniforms(s2, loc2, tslot2, nippz, tex, t_Amask, Rotatematrix, TranslateMatrix, (float)context.getTime());
		
		//setUniforms(s2, loc2, tslot2, tex, idx,4,4);
		//draw(f, s2, g3);
		setUniforms(scube, loc, tslot, TranslateMatrix,planet, (float)context.getTime(),sunPos);		
		draw(f, ssphere, sphere);
		
		setUniforms(ssphere, loc2, tslot, Rotatematrix, tex,sunPos);
		draw(f, scube, cube);
		

		/*	const float *input = context.GetJoystickAxes(0, &count);
		for (int i = 0; i < count; i++)
		{
		std::cout << "Idx" << i << ": " << input[i] << std::endl;
		}*/

	}


	freeTexture(t_magyel);
	freeTexture(t_Amask);
	freeShader(scube);
	context.Terminate();

}