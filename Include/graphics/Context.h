#pragma once

// Forward delcare GLFW's window
// handling pointer type.

struct GLFWwindow;


class Context
{
private:
	GLFWwindow *handle;
	
	
public:
	 int *axissize;

	

	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();
	void SetTime(double NewTime);


	bool IsJoystickThere(int joy);
	const float* GetJoystickAxes(int joy, int *index);
	const unsigned char* GetJoystickButtons(int joy, int* index);


	bool init(size_t w = 800, size_t h = 600, const char *title = "Graphics");

	bool step();

	bool Terminate();
};