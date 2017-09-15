#include "..\Include\graphics\Context.h"
#include "glinc.h"



#include <iostream>

using namespace std;

#ifdef _DEBUG
void APIENTRY GL_errorCallback(GLenum source, GLenum tpye, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userpram)
{
	cerr << message << endl;
}
#endif




bool Context::getKey(int key)
{
	return glfwGetKey(handle, key);
}

bool Context::getMouseButton(int button)
{
	return glfwGetMouseButton(handle, button);
}

void Context::getMousePosition(double &x_out, double &y_out)
{
	glfwGetCursorPos(handle, &x_out, &y_out);

}

double Context::getTime()
{
	return glfwGetTime();
}

void Context::SetTime(double NewTime)
{
	glfwSetTime(NewTime);
}

bool Context::IsJoystickThere(int joy)
{
	return glfwJoystickPresent(joy);
}

const float *Context::GetJoystickAxes(int joy, int *index)
{
	const float *input = glfwGetJoystickAxes(joy, index);
	return input;

}

const unsigned char * Context::GetJoystickButtons(int joy, int * index)
{
	return glfwGetJoystickButtons(joy, index);
}

bool Context::init(size_t w, size_t h, const char * title)
{
	glfwInit();

	handle = glfwCreateWindow(w, h, title, 0, 0);

	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();


#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);

	//glClearColor(0.5, 0.0, 0.5, 1.0);
#endif




	return true;

}

bool Context::step()
{
	glfwPollEvents();

	glfwSwapBuffers(handle);

	return !glfwWindowShouldClose(handle);
}

bool Context::Terminate()
{
	glfwTerminate();
	handle = nullptr;
	return true;
}
