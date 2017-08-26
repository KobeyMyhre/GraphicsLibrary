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
	context.init(800, 600);

	Geometry ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	Texture ss_diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	Shader mvplite = loadShader("../../resources/shaders/mvplite.vert",
		"../../resources/shaders/mvplite.frag");



	FrameBufer f = { 0,800,600 };

	
	int x = 0;
	int y = 0;
	int count;
	while (context.step())
	{
		const float *input = context.GetJoystickAxes(0, &count);
		if (context.IsJoystickThere(0))
		{

			for (int i = 0; i < count; i++)
			{
				std::cout << "Idx" << i << ": " << input[i] << std::endl;
			}
		}

		y += input[0] ;
		x -= input[1] ;

		int loc1 = 0;
		int loc2 = 0;
		int loc3 = 0;
		int tslot = 0;
		float turn = 0;
		if (input[4] >= 0 )
		{
			 turn += input[4];
		}
		if (input[5] >= 0)
		{
			turn += input[5];
		}
	/*	x += context.getKey('W');
		x -= context.getKey('S');
		y += context.getKey('D');
		y -= context.getKey('A');*/
		
		glm::vec3 Tpos = { y,0,x };

		glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 3, -4), Tpos, glm::vec3(0, 1, 0));
		glm::mat4 cam_proj = glm::perspective(45.f, 800.f / 600.f, .01f, 100.f);
		glm::mat4 go_model1 = glm::rotate(input[4] /3 , glm::vec3(0, -1, 0)) * glm::rotate(input[5] /3, glm::vec3(0, 1, 0));
		glm::mat4 go_model2 = glm::translate(glm::vec3(-.25f, -.5f, 0))* glm::rotate(input[2], glm::vec3(0, 0, 1));
		glm::mat4 go_model3 = glm::translate(glm::vec3(.25f, -.5f, 0)) * glm::rotate(input[2], glm::vec3(0, 0, -1));

		clearFrameBuffer(f);

		setFlags(RenderFlag::DEPTH);

		setUniforms(mvplite,loc1, tslot, cam_proj, cam_view, go_model1, ss_diffuse);
		draw(f, mvplite, ss_geo);

		setUniforms(mvplite, loc2, tslot, cam_proj, cam_view, go_model2, ss_diffuse);
		draw(f, mvplite, ss_geo);

		setUniforms(mvplite, loc3, tslot, cam_proj, cam_view, go_model3, ss_diffuse);
		draw(f, mvplite, ss_geo);
	}


	freeTexture(ss_diffuse);
	freeGeometry(ss_geo);
	freeShader(mvplite);

	context.Terminate();
}