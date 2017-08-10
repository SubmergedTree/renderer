#pragma once

#include <string>

#include<GLFW\glfw3.h>


#include "ResourceManager.h"

namespace gE
{

	class Window
	{
	public:
		Window(ResourceManager const& resourceManager);
		~Window();

		GLFWwindow* getWindow();

		int getScreenWidth();
		int getscreenHeight();

		void setAsCurrentContext();

		void swapBuffers();



	private:

		void setHints();
		void createWindow();

		int screenWidth, screenHeight;

		GLFWwindow *window;
		ResourceManager  resourceManager;
	};

}

