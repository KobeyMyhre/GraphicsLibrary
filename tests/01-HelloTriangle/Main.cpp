#include "graphics\Context.h"
#include <iostream>
#include <chrono>

using namespace std;
void main()
{
	Context context;
	context.init();
	double X = 0;
	double Y = 0;
	double Timer = 20;
	bool Defused = false;
	cout << "DEFUSE THE BOMB GO!";
	while (context.step())
	{
		cout << context.IsJoystickThere(0) << endl;


		/*if (context.getTime() > 0 && Defused == false)
		{
			cout << "Time: " << (Timer - context.getTime()) << endl;
		}
		if (context.getKey('R'))
		{
			Defused = true;
			context.SetTime(0);
			cout << "YOU DEFUSED THE BOMB!" << endl;
		}
		if (Defused == false && (Timer - context.getTime()) < 0 )
		{
			cout << "You Blew Up!" << endl;
		}*/

		/*cout << "A  is down: "<<context.getKey('A') << endl;
		cout << "M1 is down: "<<context.getMouseButton(0) << endl;
		context.getMousePosition(X, Y);
		
		cout << "X: " << X << endl;
		cout << "Y: " << Y << endl;*/
	}

	context.Terminate();
}