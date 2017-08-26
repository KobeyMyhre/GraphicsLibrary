#include "graphics\Context.h"
#include "graphics\Vertex.h"
#include "graphics\RenderObjects.h"
#include "graphics\draw.h"
#include "genShape.h"
#include <iostream>
#include <chrono>

using namespace std;
void main()
{
	int count;
	Context context;
	context.init(1200, 600);
	
	Vertex verts[4] =
	{
	{ { 0,0, 0, 1 },{ 1.0,1.0, 0.0, 1.0 } },
	{ { 1,0, 0, 1 },{ 1.0,1.0, 0.0, 1.0 } },
	{ { 0,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 } },
	{ { 1,1, 0, 1 },{ 1.0,1.0, 0.0, 1.0 } },

	
	


	};
	
	unsigned idxs[6] = {
		0,1,2,
		3,1,2
		};

	
	//Geometry g = makeGeometry(verts, 4, idxs, 6);
	Geometry g = makeNGon(8, .5f);
	
	const char* vsource =
		"#version 450\n"
		"layout(location = 0) in vec4 position;\n"
		"layout(location = 1) in vec4 color;\n"
		"out vec4 vPos;\n"
		"flat out vec4 vColor;\n"
		"void main ()\n"
		"{ \n"
		"vPos = position;\n"
		"gl_Position = position; vColor = color; }\n";

	const char* fsource =
		"#version 450\n"
		"in vec4 vPos;\n"
		"flat in vec4 vColor;\n"
		"out vec4 outColor;\n"
		"void main () {  outColor = vColor; }\n";
		
	// outcolor = vec4{1.0,0.0,0.0,1.0};
	//outColor = vPos;
	Shader s = makeShader(vsource, fsource);

	FrameBufer f = { 0,800,600 };

	double X = 0;
	double Y = 0;
	/*double Timer = 20;
	const float axes[15] = {};*/
	
	// Spawn triangles one every other loop iteration
	// int i, i ++, if(i %2)
	while (context.step())
	{
		//cout << context.IsJoystickThere(0) << endl;
		
			draw(f, s, g);
		
		
		

		/*context.GetJoystickAxes(0, context.axissize);
		
		cout << context.axissize;*/
		

		/*cout << "A  is down: "<<context.getKey('A') << endl;
		cout << "M1 is down: "<<context.getMouseButton(0) << endl;
		context.getMousePosition(X, Y);
		
		cout << "X: " << X << endl;
		cout << "Y: " << Y << endl;*/
	}
	
	freeShader(s);

	context.Terminate();
}