#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "graphics\GameObjects.h"

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
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1,1,0,1 },{},{ 0,1 },{ 0,0,1,0 } }
	};
	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangets(vquad, 4, quadidx, 6);
	Geometry quad = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 modquad = glm::rotate(glm::radians(90.f), glm::vec3(1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));

	/*Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	
	Texture spear_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float spear_gloss = 4.0f;*/

	Texture color = loadTexture("../../resources/textures/Planet.png");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");


	FrameBufer screen = { 0,800,600 };
	FrameBufer buffer = MakeFrameBuffer(1280,720,4,true,3,1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
									"../../resources/shaders/quad.frag");


	Camera cma;
	Lights L1;
	SpecGloss ss;
	ss.geo = loadGeometry("../../resources/models/soulspear.obj");
	ss.normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	ss.diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	ss.specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	ss.gloss = 4.0f;

	SpecGloss ss2 = ss;
	


	int x = 0;
	int y = 0;
	int count = 0;
	while (context.step())
	{
		int loc1 = 0;
		int loc2 = 0;
		int slot = 0;
		
		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(buffer);
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
		
	

		////lights
		//L1.dir = glm::normalize(glm::vec3(.8, -1, -1));
		//L1.proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
		//L1.view = glm::lookAt(-L1.dir, glm::vec3(0, 0, 0), glm::vec3(-1, 1, 0));

		//Camera
		glm::vec3 Tpos = { -y,0,-x };
		cma.view = glm::lookAt(glm::vec3(0, 3, -4), Tpos, glm::vec3(0, 1, 0)) * glm::rotate(rotY,glm::vec3(-1,0,0)) *  glm::rotate(rotX, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0,0, -turn * context.getTime() /3));
		cma.proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

		//Model
		ss.model = glm::rotate((float)context.getTime() / 3, glm::vec3(0, -1, 0));
		ss2.model = glm::rotate((float)context.getTime() / 3, glm::vec3(0, 0, 1));
		//Lighting
		L1.dir = glm::normalize(glm::vec3(0.5f, 0.5f, 0));
		L1.color = glm::vec4{.9f,.9f,.9f,1};
		L1.intensity = 12;
		L1.ambient = glm::vec4(.9f,.9f,.9f,1);
		L1.type = 1;



		setUniforms(standard,loc1,slot, 
					cma.proj, cma.view,
					ss.model, 
					ss.normal, ss.diffuse, ss.specular, ss.gloss,
			L1.dir, L1.color, L1.intensity, L1.ambient, L1.type);
		draw(buffer, standard, ss.geo);

		loc1 = 0;
		slot = 0;
		setUniforms(standard, loc1, slot,
			cma.proj, cma.view,
			ss2.model,
			ss2.normal, ss2.diffuse, ss2.specular, ss2.gloss,
			L1.dir, L1.color, L1.intensity, L1.ambient, L1.type);
		draw(buffer, standard, ss2.geo);


		clearFrameBuffer(screen);
		loc1 = 0;
		slot = 0;


		setUniforms(fsq_shader, loc1, slot, buffer.targets[2], (float)context.getTime());
		draw(screen, fsq_shader, quad);


	/*	setUniforms(standard, loc2, slot, cam_proj, cam_view, modquad, color, color, light_direction);
		draw(screen, standard, quad);*/

	}


	freeFrameBuffer(buffer);
	context.Terminate();

}