#include "genShape.h"
#include "graphics\RenderObjects.h"
#include "graphics\Vertex.h"
#include "math.h"
#include <iostream>
Geometry makeNGon(size_t sides, float r)
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

	


	for (int i = vsize-1; i > 0; i--)
	{
		float x = (float)(cos((angle * i) * 3.14 / 180));
			//cos angle
		float y = (float)(sin((angle * i) * 3.14 / 180));
				// sin angle
		verts[i] =  { glm::vec4{ x, y,0,1 }  ,  { abs(x),abs(y),1,1 } } ;
		 
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
	for (int i = isize -1; i >= 2; i-=3)
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
		
		std::cout << "Index: " << i << std::endl;
		std::cout << idxs[i] << std::endl;
		std::cout << idxs[i -1] << std::endl;
		std::cout << idxs[i -2] << std::endl;
		std::cout << std::endl;
		//idxs[i - 2] = idxs[i - 1] - 1;

		

		q++;
	}

	


	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;


	return ret;




	
}

Geometry MakeGrid(size_t rows, size_t columns)
{
	unsigned vsize =  rows * columns * 4;

	unsigned isize =  rows*columns * 6;

	Vertex *verts = new Vertex[vsize];
	unsigned *idxs = new unsigned[isize] {
		0, 1, 2,
		3, 1, 2
	};
	int index = 0;
	
	for (int i = 0; i < (columns * 2); i++)
	{
		float offset = .1;
		float x = 0;
		float y = 0;
		
		for (int j =0;j < (rows * 2); j++)
		{
			
				x = offset * j; //* (j/10)
				y = offset * i ; // * (j /10)
				verts[index] = { glm::vec4{ x, y,0,1 }  ,{ abs(x),abs(y),1,1 } };
			
			

				
			



			index++;
		}
		
	}
	/*for (int i = 0; i < isize - 1; i += 6)
	{
		idxs[i] = j;
		idxs[i + 1] = j + 1;
		idxs[i + 2] = j + rows;
		idxs[i + 3] = j + rows + columns;
		idxs[i + 4] = j + 1;
		idxs[i + 5] = j + rows;

		std::cout << "Index: " << i << std::endl;
		std::cout << idxs[i] << std::endl;
		std::cout << idxs[i + 1] << std::endl;
		std::cout << idxs[i + 2] << std::endl;
		std::cout << idxs[i + 3] << std::endl;
		std::cout << idxs[i + 4] << std::endl;
		std::cout << idxs[i + 5] << std::endl;
		std::cout << std::endl;



	}*/



	Geometry ret = makeGeometry(verts, vsize, idxs, isize);

	delete[] verts;
	delete[] idxs;


	return ret;
}
