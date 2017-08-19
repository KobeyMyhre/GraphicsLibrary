#pragma once


struct Geometry;
struct Shader;
struct FrameBufer;
struct Texture;

void draw(const FrameBufer &f, const Shader &s, const Geometry &g);
void setUniform(const Shader &shader, int location, float value);
void setUniform(const Shader &shader, int location, int value);
void setUniform(const Shader &shader, int location, double value);
void setUniform(const Shader &shader, int location, const Texture &value, int slot);
void clearFrameBuffer(const FrameBufer &fb);