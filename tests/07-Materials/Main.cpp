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
	glm::mat4 modquad = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));
	
	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	
	Texture floor_normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	Texture floor_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");

	Shader standard = loadShader("../../resources/shaders/standard.vert",
		"../../resources/shaders/standard.frag");


	FrameBufer screen = { 0,800,600 };

	int x = 0;
	int y = 0;
	int count = 0;
	while (context.step())
	{
		int loc = 0;
		int slot = 0;
		clearFrameBuffer(screen);
		setFlags(RenderFlag::DEPTH);

		const float *input = context.GetJoystickAxes(0, &count);
		if (context.IsJoystickThere(0))
		{

			for (int i = 0; i < count; i++)
			{
				std::cout << "Idx" << i << ": " << input[i] << std::endl;
			}
		}
		float turn = 0;
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

		glm::vec3 Tpos = { -y,0,-x };
		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), Tpos, glm::vec3(0, 5, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
		glm::mat4 go_model = glm::rotate(input[4] , glm::vec3(0, -1, 0)) * glm::rotate(input[5] , glm::vec3(0, 1, 0))* glm::scale(glm::vec3(5, 5, 1)) *  glm::translate(glm::vec3(0, -.5f, 5));
		glm::vec3 light_direction = glm::normalize(glm::vec3(1, -1, 1));

		setUniforms(standard,loc,slot, cam_proj, cam_view, go_model, floor_normal, floor_diffuse,light_direction);
		draw(screen, standard, ss_geo);

	}
	context.Terminate();

}