#pragma once
#include "glm\glm.hpp"
#include "glm\ext.hpp"

struct Transform
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::mat3 rotation; // best to use an interface or helper function

	Transform *parent = nullptr;

	glm::mat4 getLocal() const; // evaluate local matrix: (T*R*S)
	glm::mat4 getGlobal() const; // evaluate global: parent.global * local

								 // helpers for setting a meaningful rotation:
	//void axisAngle(float angle, const glm::vec3 &axis = { 0,1,0 });
	void lookAt(const glm::vec3 &target, const glm::vec3 &up = { 0,1,0 });
};
