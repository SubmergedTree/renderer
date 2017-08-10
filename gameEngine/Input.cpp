#include "Window.h"
#include "Input.h"


#include <vector>
#include <map>
#include<iostream>

namespace gE
{

	struct CallbackMouse
	{
		std::function< void(double, double) > callback;

		void call(double x, double y)
		{
			callback(x, y);
		}
	};

	struct CallbackKey
	{
		std::function< void(int) > callback;

		void call(int key)
		{
			callback(key);
		}
	};

	struct CallbackResize
	{
		std::function<void(int width, int height)> callback;

		void call(int width, int height)
		{
			callback(width, height);
		}

	};

	struct CallbackScroll
	{
		std::function<void(double xOffset, double yOffset)> callback;

		void call(double xOffset, double yOffset)
		{
			callback(xOffset, yOffset);
		}
	};


//	std::vector<CallbackMouse> callbackOnMouseMoves;
//	std::vector<CallbackKey> callbackOnKeyDown;
//	std::vector<CallbackResize> callbackOnResize;
//	std::vector<CallbackScroll> callbackOnScroll;

	std::map<unsigned long, CallbackMouse> callbackOnMouseMoves;
	std::map<unsigned long, CallbackKey> callbackOnKeyDown;
	std::map<unsigned long, CallbackResize> callbackOnResize;
	std::map<unsigned long, CallbackScroll> callbackOnScroll;

	unsigned long callbackMouseKey = 0;
	unsigned long callbackKeyKey = 0;
	unsigned long callbackScrollKey = 0;
	unsigned long callbackResizeKey = 0;


	void onResize(GLFWwindow* window, int width, int height)
	{
		for (auto it : callbackOnResize)
		{
			//it.call(width, height);
			it.second.call(width, height);
		}
	}

	void onMouseMove(GLFWwindow* window, double xpos, double ypos)
	{
		for (auto it : callbackOnMouseMoves)
		{
			//it.call(xpos,ypos);
			it.second.call(xpos, ypos);
		}
	}

	void onScroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		for (auto it : callbackOnScroll)
		{
			//it.call(xoffset, yoffset);
			it.second.call(xoffset, yoffset);
		}
	}

	void onKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		for (auto it : callbackOnKeyDown)
		{
			//it.call(key);
			it.second.call(key);
		}
	}


	Window * localWindow;

	void initInput(Window * window)
	{
		localWindow = window;
		glfwSetFramebufferSizeCallback(window->getWindow(), onResize);
		glfwSetCursorPosCallback(window->getWindow(), onMouseMove);
		glfwSetScrollCallback(window->getWindow(), onScroll);
		glfwSetKeyCallback(window->getWindow(), onKeyDown);
		
	}



	unsigned long registerCallbackOnMouseMove(std::function<void(double, double)> callback)
	{
		CallbackMouse cb;
		cb.callback = callback;
		//callbackOnMouseMoves.push_back(cb);
		callbackOnMouseMoves.insert(std::pair<unsigned long, CallbackMouse>(++callbackMouseKey,cb));
		return callbackMouseKey;
	}

	unsigned long registerCallbackOnKeyPressed(std::function<void(int)> callback)
	{
		CallbackKey ck;
		ck.callback = callback;
		//callbackOnKeyDown.push_back(ck);
		callbackOnKeyDown.insert(std::pair<unsigned long, CallbackKey>(++callbackKeyKey, ck));
		return callbackKeyKey;
	}

	unsigned long registerCallbackOnScroll(std::function<void(double , double )> callback)
	{
		CallbackScroll cs;
		cs.callback = callback;
		//callbackOnScroll.push_back(cs);
		callbackOnScroll.insert(std::pair<unsigned long, CallbackScroll>(++callbackScrollKey, cs));
		return callbackScrollKey;
	}

	unsigned long registerCallbackOnResize(std::function<void(int , int )> callback)
	{
		CallbackResize cr;
		cr.callback = callback;
		//callbackOnResize.push_back(cr);
		callbackOnResize.insert(std::pair<unsigned long, CallbackResize>(++callbackResizeKey, cr));
		return callbackResizeKey;
	}

	void deleteCallbackOnMouseMove(unsigned long key)
	{
		callbackOnMouseMoves.erase(key);
	}

	void deleteCallbackOnScroll(unsigned long key)
	{
		callbackOnScroll.erase(key);
	}

	void deleteCallbackOnResize(unsigned long key)
	{
		callbackOnResize.erase(key);
	}

	void deleteCallbackOnKeyPressed(unsigned long key)
	{
		callbackOnKeyDown.erase(key);
	}




	Input::Input()
	{
		glfwSetInputMode(localWindow->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	bool Input::isKeyPressed(int key)
	{
		int state = glfwGetKey(localWindow->getWindow(), key);

		if (state == GLFW_PRESS)
		{
			return true;
		}

		return false;
	}
	float Input::getMouseX()
	{
		double xpos, ypos;
		glfwGetCursorPos(localWindow->getWindow(), &xpos, &ypos);
		return xpos;
	}
	float Input::getMouseY()
	{
		double xpos, ypos;
		glfwGetCursorPos(localWindow->getWindow(), &xpos, &ypos);
		return ypos;
	}




}

