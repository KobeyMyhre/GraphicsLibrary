#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"


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

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	
	Texture spear_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	float spear_gloss = 4.0f;

	Texture color = loadTexture("../../resources/textures/Planet.png");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");


	FrameBufer screen = { 0,800,600 };
	FrameBufer buffer = MakeFrameBuffer(1280,720,4,true,3,1);

	Shader fsq_shader = loadShader("../../resources/shaders/quad.vert",
									"../../resources/shaders/quad.frag");


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

		//Controls
		const float *input = context.GetJoystickAxes(0, &count);
		if (context.IsJoystickThere(0))
		{

			for (int i = 0; i < count; i++)
			{
				std::cout << "Idx" << i << ": " << input[i] << std::endl;
			}
		}
		float turn = 0;
		float rotY = 0;
		float rotX = 0;
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




		//Camera
		glm::vec3 Tpos = { -y,0,-x };
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), Tpos, glm::vec3(0, 1, 0)) * glm::rotate(rotY,glm::vec3(-1,0,0)) *  glm::rotate(rotX, glm::vec3(0, -1, 0)) * glm::translate(glm::vec3(0,0, -turn * context.getTime() /3));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);

		//Model
		glm::mat4 go_model = glm::rotate((float)context.getTime() / 3, glm::vec3(0, -1, 0));

		//Lighting
		glm::vec3 light_direction = glm::normalize(glm::vec3(0.5f, 0.5f, 0));
		glm::vec4 l_color = glm::vec4{.9f,.9f,.9f,1};
		float l_intensity = 12;
		glm::vec4 l_ambient = glm::vec4(.9f,.9f,.9f,1);
		int l_type = 1;



		setUniforms(standard,loc1,slot, 
					cam_proj, cam_view, 
					go_model, 
					spear_normal, spear_diffuse, spear_specular, spear_gloss,
					light_direction, l_color, l_intensity, l_ambient, l_type);
		draw(buffer, standard, ss_geo);


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