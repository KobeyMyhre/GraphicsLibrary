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
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangets(vquad, 4, quadidx, 6);
	Geometry floor_geo = makeGeometry(vquad, 4, quadidx, 6);
	glm::mat4 floor_model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0))
		* glm::scale(glm::vec3(5, 5, 1));

	// SoulSpear
	Geometry  ss_geo = loadGeometry("../../resources/models/soulspear.obj");
	glm::mat4 ss_model; // = glm::rotate(time, glm::vec3(0,1,0)) // on update.

	// Cube
	Geometry cube_geo = loadGeometry("../../resources/models/cube.obj");
	glm::mat4 cube_model = glm::translate(glm::vec3(2, 1, -1));


	Texture texColor = loadTexture("../../resources/textures/Planet.png");

	//	Camera
	

	// Light
	glm::vec3 light_dir = glm::normalize(glm::vec3(.8, -1, -1));
	glm::mat4 light_proj = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view = glm::lookAt(-light_dir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 color = glm::vec4(1, 0, 1, 1);
	//Second Light
	// Light2
	glm::vec3 light_dir2 = glm::normalize(glm::vec3(-1, -.8, 1));
	glm::mat4 light_proj2 = glm::ortho<float>(-10, 10, -10, 10, -10, 10);
	glm::mat4 light_view2 = glm::lookAt(-light_dir2, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::vec4 color2 = glm::vec4(.5f, .5f, 1, 1);

	// Shaders
	Shader shdr_shadow = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");
	Shader shdr_direct = loadShader("../../resources/shaders/direct.vert",
		"../../resources/shaders/direct.frag");


	FrameBufer fb_shadow = MakeFrameBuffer(2048, 2048, 0, true, 0, 0);
	FrameBufer fb_shadow2 = MakeFrameBuffer(2048, 2048, 0, true, 0, 0);
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


		
		
		ss_model = glm::rotate(time, glm::vec3(0, glm::sin(time), 0)); // on update.

		
														  // Shadow Pass
		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(fb_shadow, false, true);

		int loc = 0;
		int slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, floor_model, texColor);
		draw(fb_shadow, shdr_shadow, floor_geo);
		
		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, ss_model, texColor);
		draw(fb_shadow, shdr_shadow, ss_geo);

		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj, light_view, cube_model, texColor);
		draw(fb_shadow, shdr_shadow, cube_geo);


		//Second Light
		/*setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(fb_shadow2, false, true);

		 loc = 0;
		 slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj2, light_view2, floor_model);
		draw(fb_shadow2, shdr_shadow, floor_geo);

		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj2, light_view2, ss_model);
		draw(fb_shadow2, shdr_shadow, ss_geo);

		loc = slot = 0;
		setUniforms(shdr_shadow, loc, slot, light_proj2, light_view2, cube_model);
		draw(fb_shadow2, shdr_shadow, cube_geo);*/





		setFlags(RenderFlag::DEPTH);
		clearFrameBuffer(screen);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			floor_model,            // Geometry Data
			light_proj, light_view, light_proj2, light_view2, // Light Data
			fb_shadow.depthTarget, texColor,color, color2); // Shadow Map
		draw(screen, shdr_direct, floor_geo);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			ss_model,            // Geometry Data
			light_proj, light_view, light_proj2, light_view2, // Light Data
			fb_shadow.depthTarget, texColor, color, color2); // Shadow Map
		draw(screen, shdr_direct, ss_geo);

		loc = slot = 0;
		setUniforms(shdr_direct, loc, slot,
			cam_proj, cam_view,     // Camera Data
			cube_model,            // Geometry Data
			light_proj, light_view, light_proj2, light_view2, // Light Data
			fb_shadow.depthTarget, texColor, color, color2); // Shadow Map
		draw(screen, shdr_direct, cube_geo);
		//... other geometry
	}
}