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
	glm::mat4 floor_model = glm::scale(glm::vec3(1,1, 1)) * glm::rotate(glm::radians(90.f), glm::vec3(0, 2, 0));// = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
	glm::mat4 middle_Mod = glm::translate(glm::vec3(-2, 0, 0));
	glm::mat4 middle_Mod2 = glm::translate(glm::vec3(-1, 3, 0)) *glm::scale(glm::vec3(0.5f, 5, 0.5f));
//* glm::scale(glm::vec3(5, 5, 1));

	Geometry cube = loadGeometry("../../resources/models/cube.obj");
	Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	Geometry plane = MakeGrid(5, 1);
	Geometry Ngon = makeNGon(16, .5f);
	//Geometry sphere = loadGeometry("../../resources/models/sphere.obj");
	Geometry ss = loadGeometry("../../resources/models/soulspear.obj");
	
	Shader SphereTess = loadShader("../../resources/shaders/STess.vert",
							 "../../resources/shaders/STess.frag",
							 "../../resources/shaders/STess.geom",
							 "../../resources/shaders/STess.cntrl",
							 "../../resources/shaders/STess.eval");

	Shader QuadTess = loadShader("../../resources/shaders/QTess.vert",
		"../../resources/shaders/QTess.frag",
		"../../resources/shaders/QTess.geom",
		"../../resources/shaders/QTess.cntrl",
		"../../resources/shaders/QTess.eval");

	Shader Tess = loadShader("../../resources/shaders/Tess.vert",
		"../../resources/shaders/Tess.frag",
		"../../resources/shaders/Tess.cntrl",
		"../../resources/shaders/Tess.eval");

	/*Texture texColor = loadTexture("../../resources/textures/Wavy.PNG");
	Texture texColor2 = loadTexture("../../resources/textures/Pink2.PNG");*/
	

	Texture Ambient = loadTexture("../../resources/textures/earth_normal.jpg");
	Texture Diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	
	Texture Ambient2 = loadTexture("../../resources/textures/pattern_51_height.png");
	Texture Diffuse2 = loadTexture("../../resources/textures/pattern_51_diffus.png");
	Texture Specular2 = loadTexture("../../resources/textures/pattern_51_specular.png");
	
	Texture Ambient5 = loadTexture("../../resources/textures/pattern_73_height.png");
	Texture Diffuse5 = loadTexture("../../resources/textures/pattern_73_diffus.png");

	Texture Specular6 = loadTexture("../../resources/textures/pattern_35_specular.png");
	Texture Diffuse6 = loadTexture("../../resources/textures/pattern_35_diffus.png");

	Texture Ambient3 = loadTexture("../../resources/textures/soulspear_specular.tga");
	Texture Diffuse3 = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	// Light
	glm::vec3 light_pos = glm::normalize(glm::vec3(.8, 2, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_pos, glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
	glm::vec4 color = glm::vec4(0.3f, 0.3f, 0, 1);
	
	
	//Tesselation
	float TessLvlInner = 1; //3
	float TessLvlOuter = 1; //6
	glm::vec3 AmbientColor = glm::vec3(1, 1, 0);
	glm::vec3 DiffuseColor = glm::vec3(0, 1, 1);
	glm::vec3 SpecularColor = glm::vec3(.5f, .5f, .5f);
	

	/////////////////////////////////////////////
	/////////////////////////////////////////////
	/////////////////////////////////////////////

	//////http://codeflow.org/entries/2010/nov/07/opengl-4-tessellation/

	/////////////////////////////////////////////
	/////////////////////////////////////////////
	/////////////////////////////////////////////

	
	FrameBufer screen = { 0,1280, 720 };


	float x = 0;
	float y = 0;
	float turn = 0;
	float rotY = 0;
	float rotX = 0;
	float Damper = 0.1f;
	int count = 0;
	int Bcount = 0;
	while (context.step())
	{
		float time = context.getTime();

		
		
		//Controls
		const float *input = context.GetJoystickAxes(0, &count);
		const unsigned char *buttons = context.GetJoystickButtons(0, &Bcount);
		if (buttons[4] == 1)
		{
			TessLvlInner+= Damper;
		}
		if (buttons[5] == 1)
		{
			TessLvlOuter+= Damper;
		}

		if (buttons[0] == 1)
		{
			TessLvlInner--;
			TessLvlOuter--;

			if (TessLvlInner <= 0) { TessLvlInner = 1; }
			if (TessLvlOuter <= 0) { TessLvlOuter = 1; }
		}


		if (context.IsJoystickThere(0))
		{

			for (int i = 0; i < count; i++)
			{
				std::cout << "Idx" << i << ": " << (int)buttons[i] << std::endl;
			}
			rotY += input[3] * Damper;
			rotX += input[2]* Damper;
			
			y += input[0] * Damper;
			x -= input[1] * Damper;
			
			if (input[4] >= 0)
			{
				turn += input[4] * Damper;
			}
			if (input[5] >= 0)
			{
				turn -= input[5] * Damper;
			}
			std::cout << "X: " << x << " Y: " << y << std::endl;
			std::cout << "turn: " << turn << std::endl;
		}
		//	Camera
		glm::mat4 cam_view = glm::lookAt(glm::vec3(2, 2, 5),
			glm::vec3(-y, 1, -x + -3),
			glm::vec3(0, 1, 0)) * glm::rotate(rotY, glm::vec3(-1, 0, 0)) *  glm::rotate(rotX, glm::vec3(0, 0, -1)) * glm::translate(glm::vec3(0, 0, (-turn  / 3)));
		glm::mat4 cam_proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);


		glm::mat4 modelView = cam_view * floor_model;
		glm::mat4 modelView2 = cam_view * middle_Mod;
		glm::mat4 modelView3 = cam_view * middle_Mod2;
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(modelView));

		glm::mat4 B = glm::mat4(-1,3,-3,1,
								3,-6,3,0,
								-3,3,0,0,
								1,0,0,0);

		glm::mat4 B1 = glm::mat4(-1, 1, -1, 1,
							 	  1,-1,  1, 0,
								 -1, 1,  0, 0,
								  1, 0,  0, 0);
		
		glm::mat4 Bt = glm::transpose(B);

		

		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(screen);


														   // Shadow Pass
		
		int loc = 0;
		int slot = 0;
		
																									// Texture   //texture					
		setUniforms(SphereTess, loc, slot, TessLvlInner, TessLvlOuter, cam_proj, modelView, light_pos, Specular6, Diffuse6, normalMatrix );
		
		Stess_draw(screen, SphereTess, cube);
		float shiny = 1.5f;

		 loc = 0;
		 slot = 0;

		


		
		setUniforms(QuadTess, loc, slot, TessLvlInner, TessLvlOuter, cam_proj, modelView2, light_pos, DiffuseColor, AmbientColor,SpecularColor ,shiny,normalMatrix, B ,Bt);

		Qtess_draw(screen, QuadTess, ss);
		glm::vec2 ScreenSize = glm::vec2(1280, 720);
		/*setUniforms(Tess, loc, slot, Ambient2, ScreenSize, modelView, shiny, Diffuse2, Specular2);

		Tess_draw(screen, Tess, ss); */

		
		//... other geometry
	}
}