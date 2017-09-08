#include "graphics\Context.h"
#include "graphics\Vertex.h"
//#include "graphics\RenderObjects.h"
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
	context.init(1280,720);


	Vertex vquad[] = {
		{ { -1,-1,0,1 },{},{ 0,0 },{ 0,0,1,0 } },
		{ { 1,-1,0,1 },{},{ 1,0 },{ 0,0,1,0 } },
		{ { 1, 1,0,1 },{},{ 1,1 },{ 0,0,1,0 } },
		{ { -1, 1,0,1 },{},{ 0,1 },{ 0,0,1,0 } } };

	unsigned quadidx[] = { 0,1,3, 1,2,3 };
	solveTangets(vquad, 4, quadidx, 6);
	




	SpecGloss objects[3];

	//quad
	objects[0].geo = makeGeometry(vquad, 4, quadidx, 6);
	objects[0].diffuse = loadTexture("../../resources/textures/four_diffuse.tga");
	objects[0].specular = loadTexture("../../resources/textures/four_specular.tga");
	objects[0].normal = loadTexture("../../resources/textures/four_normal.tga");
	objects[0].model = glm::rotate(glm::radians(90.f), glm::vec3(-1, 0, 0)) * glm::scale(glm::vec3(5, 5, 1));
	objects[0].gloss = 4;
	//Soulspear
	objects[1].geo = loadGeometry("../../resources/models/soulspear.obj");
	objects[1].normal = loadTexture("../../resources/textures/soulspear_normal.tga");
	objects[1].diffuse = loadTexture("../../resources/textures/soulspear_diffuse.tga");
	objects[1].specular = loadTexture("../../resources/textures/soulspear_specular.tga");
	objects[2].gloss = 4;
	//Earth
	objects[2].geo = loadGeometry("../../resources/models/sphere.obj");
	objects[2].diffuse = loadTexture("../../resources/textures/earth_diffuse.jpg");
	objects[2].specular = loadTexture("../../resources/textures/earth_specular.jpg");
	objects[2].normal = loadTexture("../../resources/textures/earth_normal.jpg");
	objects[2].model = glm::scale(glm::vec3(2, 2, 2)) * glm::translate(glm::vec3(2, 1, -1));
	objects[2].gloss = 4;

	Camera cam;
	cam.view = glm::lookAt(glm::vec3(0, 2, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	cam.proj = glm::perspective(45.f, 1280.f / 720.f, 1.f, 10.f);

	DLite lights[2];

	lights[0].range = 10;
	lights[0].intensity = 1;
	lights[0].color = glm::vec4(1, 0, 1, 1);
	lights[0].direction = glm::vec3(1, 1, 0);

	lights[1].range = 10;
	lights[1].intensity = 1;
	lights[1].color = glm::vec4(0, 1, 0, 1);
	lights[1].direction = glm::vec3(-.5f, 0, 0);


	Shader gpass = loadShader("../../resources/shaders/gpass.vert",
		"../../resources/shaders/gpass.frag");

	Shader cpass = loadShader("../../resources/shaders/cpass.vert",
		"../../resources/shaders/cpass.frag");

	Shader lpassD = loadShader("../../resources/shaders/lpassD.vert",
		"../../resources/shaders/lpassD.frag");

	Shader spassD = loadShader("../../resources/shaders/shadow.vert",
		"../../resources/shaders/shadow.frag");

	FrameBufer screen = { 0,1280,720 };
	FrameBufer gbuffer = MakeFrameBuffer(1280, 720, 4, true, 2, 2);
	FrameBufer lbuffer = MakeFrameBuffer(1280, 720, 4, false, 2, 0);
	FrameBufer sbuffer = MakeFrameBuffer(1024, 1024, 0, false, 0, 0);


	int loc = 0, slot = 0;
	while (context.step())
	{
		objects[1].model = glm::rotate((float)context.getTime(), glm::vec3(0, 1, 0));
		//Gpass
		clearFrameBuffer(gbuffer);
		setFlags(RenderFlag::DEPTH);

		for (int i = 0; i < 3; ++i)
		{
			loc = 0;
			slot = 0;
			setUniforms(gpass, loc, slot, cam, objects[i]);
			draw(gbuffer, gpass, objects[i].geo);
		}

		//Lpass
		clearFrameBuffer(lbuffer);
		
		for (int i = 0; i < 2; ++i)
		{
			clearFrameBuffer(sbuffer);
			setFlags(RenderFlag::ADDITIVE);
			
			for (int i = 0; i < 3; ++i)
			{
				loc = 0;
				slot = 0;
				setUniforms(spassD, loc, slot, lights[i].getProj(), lights[i].getView(), objects[i].model);
				draw(sbuffer, spassD, objects[i].geo);
			}

			setFlags(RenderFlag::ADDITIVE);
			for (int i = 0; i < 3; ++i)
			{
				loc = 0;
				slot = 0;
				setUniforms(lpassD, loc, slot,
														cam, 
														 objects[i].model,
														lights[i], 
													gbuffer.targets[3], gbuffer.targets[2], sbuffer.depthTarget,
													objects[i].gloss );
				draw(lbuffer, lpassD, objects[0].geo);
			}

			
			
			
		}



		//Cpass
		loc = 0;
		slot = 0;
		clearFrameBuffer(screen);
		setUniforms(cpass, loc, slot, gbuffer.targets[0], lbuffer.targets[0]);
		draw(screen, cpass, objects[0].geo);





	}
	context.Terminate();

	

}