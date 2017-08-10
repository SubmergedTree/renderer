#pragma once

#include "Window.h"

#include <GLFW\glfw3.h>


#include <functional>

#define MOUSE_CALLBACK_ARGS std::placeholders::_1,std::placeholders::_2
#define KEY_CALLBACK_ARGS std::placeholders::_1
#define SCROLL_CALLBACK_ARGS std::placeholders::_1,std::placeholders::_2
#define RESIZE_CALLBACK_ARGS std::placeholders::_1,std::placeholders::_2

//TODO by callbacks used within classes: Delete object in vector when instance in class is deleted.
//Return index from vector in registerCallback... and delete it with the helb of the destructor
//.call there another function which deletes from vector

namespace gE
{

	extern void initInput(Window * window);


	extern unsigned long registerCallbackOnMouseMove(std::function< void(double,double) > callback);
	extern unsigned long registerCallbackOnKeyPressed(std::function< void(int) > callback);
	extern unsigned long registerCallbackOnScroll(std::function< void(double, double ) > callback);
	extern unsigned long registerCallbackOnResize(std::function< void(int , int ) > callback);


	void deleteCallbackOnMouseMove(unsigned long key);
	void deleteCallbackOnKeyPressed(unsigned long key);
	void deleteCallbackOnMouseMove(unsigned long key);
	void deleteCallbackOnScroll(unsigned long key);
	void deleteCallbackOnResize(unsigned long key);


	class Input
	{
	public:
		Input();


		bool isKeyPressed(int key);

		float getMouseX();
		float getMouseY();

	private:
	};



}