#include "Window.h"

#include<iostream>


namespace gE
{

	Window::Window(ResourceManager const& resourceManager)
	{
		this->resourceManager = resourceManager;
		setHints();
		createWindow();
	}


	Window::~Window()
	{
		glfwSetWindowShouldClose(window, true);

		//glfwTerminate();
	}

	GLFWwindow * Window::getWindow()
	{
		return window;
	}

	int Window::getScreenWidth()
	{
		return screenWidth;
	}

	int Window::getscreenHeight()
	{
		return screenHeight;
	}

	void Window::setAsCurrentContext()
	{
		glfwMakeContextCurrent(window);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void Window::setHints()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	void Window::createWindow()
	{
		int width = resourceManager.getIntFromStringPairFile("config.txt","width");
		int height = resourceManager.getIntFromStringPairFile("config.txt", "height");

		std::string title = "default";
		try
		{
			 title = resourceManager.getStringFromStringPairFile("config.txt", "windowTitle");
		}
		catch (int e)
		{
			std::cout << "error" << std::endl;
		}

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	}

}