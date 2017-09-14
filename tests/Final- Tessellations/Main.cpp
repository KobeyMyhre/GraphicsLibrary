#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "GenShape.h"

#include <iostream>
#include <random>
#include "graphics\Load.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"


void main()
{
	Context context;
	context.init();



	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },	//0
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },	//1
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },	//2
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };	//3

	unsigned quadidx[] = { 1,2,3, 0,1,3 };
	solveTangets(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::scale(glm::vec3(5, .5f, 5)) ;// = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		//* glm::scale(glm::vec3(5, 5, 1));

	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	Geometry plane = MakeGrid(5, 1);
	Geometry Ngon = makeNGon(16, .5f);
	//Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	//Geometry ss = loadGeometry("../../resources/models/soulspear.obj");
	
	Shader Tess = loadShader("../../resources/shaders/Tess.vert",
							 "../../resources/shaders/Tess.frag",
							 "../../resources/shaders/Tess.geom",
							 "../../resources/shaders/Tess.cntrl",
							 "../../resources/shaders/Tess.eval");

	/*Texture texColor = loadTexture("../../resources/textures/Wavy.PNG");
	Texture texColor2 = loadTexture("../../resources/textures/Pink2.PNG");*/
	

	Texture Ambient = loadTexture("../../resources/textures/earth_normal.jpg");
	Texture Diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	
	Texture Ambient2 = loadTexture("../../resources/textures/pattern_51_height.png");
	Texture Diffuse2 = loadTexture("../../resources/textures/pattern_51_diffus.png");
	
	Texture Ambient3 = loadTexture("../../resources/textures/soulspear_specular.tga");
	Texture Diffuse3 = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	// Light
	glm::vec3 light_pos = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_pos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 color = glm::vec4(0.3f, 0.3f, 0, 1);
	
	
	//Tesselation
	float TessLvlInner = 1; //3
	float TessLvlOuter = 1.5f; //6
	glm::vec3 AmbientColor = glm::vec3(1, 0, 0);
	glm::vec3 DiffuseColor = glm::vec3(0, 1, 0);
	

	/////////////////////////////////////////////
	/////////////////////////////////////////////
	/////////////////////////////////////////////

	//////http://codeflow.org/entries/2010/nov/07/opengl-4-tessellation/

	/////////////////////////////////////////////
	/////////////////////////////////////////////
	/////////////////////////////////////////////

	
	FrameBufer screen = { 0,1280, 720 };


	int x = 0;
	int y = 0;
	int count = 0;
	while (context.step())
	{
		float time = context.getTime();

		float turn = 0;
		float rotY = 0;
		float rotX = 0;
		//Controls
		const float *input = context.GetJoystickAxes(0, &count);
		if (context.IsJoystickThere(0))
		{

			for (int i = 0; i < count; i++)
			{
				std::cout << "Idx" << i << ": " << input[i] << std::endl;
			}
			rotY += input[3] /** context.getTime()*/;
			rotX += input[2]/* * context.getTime()*/;
			y += input[0];
			x -= input[1];
			if (input[4] >= 0)
			{
				turn += input[4];
			}
			if (input[5] >= 0)
			{
				turn += input[5];
			}
		}
		//	Camera
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 2, 5),
			glm::vec3(-y, 1, -x),
			glm::vec3(0, 1, 0)) * glm::rotate(rotY, glm::vec3(-1, 0, 0)) *  glm::rotate(rotX, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0, 0, -turn * context.getTime() / 3));
		glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);


		glm::mat4 modelView = cam_view * floor_model;
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelView));

		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(screen);


																	   // Shadow Pass
		

		int loc = 0;
		int slot = 0;
		
																									// Texture   //texture					
		setUniforms(Tess, loc, slot, TessLvlInner, TessLvlOuter, cam_proj, modelView, light_pos, Diffuse3, Ambient3, normalMatrix );
		
		tess_draw(screen, Tess, cube);




		

		
		//... other geometry
	}
}