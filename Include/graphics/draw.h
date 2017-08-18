#pragma once


struct Geometry;
struct Shader;
struct FrameBufer;

void draw(const FrameBufer &f, const Shader &s, const Geometry &g);
