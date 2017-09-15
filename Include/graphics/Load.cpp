#include "Load.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"

#include <random>
#include "Vertex.h"
#include <fstream>
#include <string>
using namespace std;


Texture loadTexture(const char * path)
{
	Texture retval = { 0 };

	stbi_set_flip_vertically_on_load(true);
	int w, h, c;
	unsigned char *pixels;
	pixels =  stbi_load(path, &w,&h,&c, STBI_default) ;

	retval = makeTexture(w, h, c, pixels);
	stbi_image_free(pixels);

	return retval;
}

string fileToString(const char *path)
{
	/*std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));*/


	std::ifstream file(path);
	std::string temp;
	std::string finalz;
	if (file.is_open())
	{
		while (getline(file, temp))
		{
			finalz += temp + "\n";
		}
	}
	
	//const char *retval = temp.c_str;
	return finalz;

}


Shader loadShader(const char * vpath, const char * fpath)
{
	Shader retval = { 0 };

	string v = fileToString(vpath);
	string f = fileToString(fpath);


	const char *vsource = v.c_str();
	const char *fsource = f.c_str();



	retval = makeShader(vsource, fsource);

	return retval;

}

Shader loadShader(const char * vpath, const char * fpath, const char * Gpath, const char * Cpath, const char * Epath)
{
	Shader retval = { 0 };

	string v = fileToString(vpath);
	string f = fileToString(fpath);
	string c = fileToString(Cpath);
	string e = fileToString(Epath);
	string G = fileToString(Gpath);

	const char *vsource = v.c_str();
	const char *fsource = f.c_str();
	const char *csource = c.c_str();
	const char *esource = e.c_str();
	const char *gsource = G.c_str();

	retval = makeShader(vsource, fsource, gsource, csource,esource);

	return retval;
}

Shader loadShader(const char * vpath, const char * fpath, const char * Cpath, const char * Epath)
{
	Shader retval = { 0 };

	string v = fileToString(vpath);
	string f = fileToString(fpath);
	string c = fileToString(Cpath);
	string e = fileToString(Epath);
	

	const char *vsource = v.c_str();
	const char *fsource = f.c_str();
	const char *csource = c.c_str();
	const char *esource = e.c_str();
	

	retval = makeShader(vsource, fsource, csource, esource);

	return retval;
}

glm::vec4 randColor()
{
	return{ rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,1 };
}

Geometry loadGeometry(const char * path)
{
	Geometry retval = { 0,0,0,0 };
	std::vector<tinyobj::shape_t> shapes;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);
	size_t isize = shapes[0].mesh.indices.size();
	size_t *indices = new unsigned[isize];

	size_t vsize = isize;
	Vertex *verts = new Vertex[vsize];

	for (int i = 0; i < isize; ++i)
	{
		indices[i] = i;

		int ni = shapes[0].mesh.indices[i].normal_index;
		int pi = shapes[0].mesh.indices[i].vertex_index;
		int ti = shapes[0].mesh.indices[i].texcoord_index;
		
		const float *p = &attrib.vertices[pi *3]; //3x
		const float *n = &attrib.normals[ni *3]; //3x
		const float *t = &attrib.texcoords[ti *2]; //2x
		
		verts[i].position = {p[0],p[1],p[2],1};
		verts[i].UV = { t[0], t[1] };
		verts[i].norms = { n[0],n[1],n[2],0 };
	
		
	}

	//for (size_t i = 0; i < vsize; ++i)
	//{
	//	const float *p = &attrib.vertices[i * 3];
	//	verts[i].position = { p[0], p[1], p[2], 1 };
	//	verts[i].color = randColor();
	//	verts[i].UV = { p[0], p[1] };
	//	
	//}

	
	/*for (size_t i = 0; i < isize; ++i)
	{
		indices[i] = shapes[0].mesh.indices[i].vertex_index;
	}*/
	solveTangets(verts, vsize, indices, isize);
	retval = makeGeometry(verts, vsize, indices, isize);

	delete[] verts;
	delete[] indices;


	return retval;
}




