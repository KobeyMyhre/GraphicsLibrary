#include "GenShape.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "math.h"
#include <iostream>
#include <random>
Geometry makeNGon(size_t sides, float r, float size)
{

	int angle = 360 / sides;
	unsigned vsize = sides + 1;

	unsigned isize = sides * 3;

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize]; /*{7,0,1,
										  7,1,2,
										  7,2,3,
										  7,3,4,
										  7,4,5,
										  7,5,6,
										  7,6,0};*/




	for (int i = vsize - 1; i >=
		0; i--)
	{
		float x = (float)(cos((angle * i) * 3.14159265 / 180));
		//cos angle
		float y = (float)(sin((angle * i) * 3.14159265 / 180));
		// sin angle
		x *= size;
		y *= size;

		float UVx = (float)(cos((angle * i) * 3.14 / 180));
		float UVy = (float)(cos((angle * i) * 3.14 / 180));

		verts[i] = { glm::vec4{ x, y,0,1 }  ,{ abs(x),0,abs(y),1 }, glm::vec2{ i % 2,((i + 1) % 2) } };

		/*if (i == vsize)
		{
		verts[0] = { {{ 0,0,0,0}}, {{0,0,1,1}} };
		}
		else
		{
		verts[i] = verts[i - 1] * r;
		}*/
	}
	int q = 2;
	for (int i = isize - 1; i >= 2; i -= 3)
	{
		if (i != 2)
		{
			idxs[i] = vsize - q;
			idxs[i - 1] = vsize - q - 1;
			idxs[i - 2] = vsize - 1;
		}
		else
		{
			idxs[i] = vsize - q;
			idxs[i - 1] = vsize - 2;
			idxs[i - 2] = vsize - 1;
		}


		//idxs[i - 2] = idxs[i - 1] - 1;



		q++;
	}




	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;


	return ret;





}