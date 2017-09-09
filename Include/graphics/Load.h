#pragma once
#include "RenderObjects.h"

Texture loadTexture(const char *path);

Shader loadShader(const char *vpath, const char *fpath);
Shader loadShader(const char *vpath, const char *fpath, const char *Gpath, const char *Cpath, const char *Epath);
Geometry loadGeometry(const char * path);