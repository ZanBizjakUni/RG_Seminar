#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "DProps.h"
#include "InputManager.h"

namespace DEngine {

	///class Ignition
	/*
	* class that sets up the window and
	* initialises GLFW and glad (OpenGL)
	*/
	class Ignition {
	public:
		Ignition();
		~Ignition();
		///GLFWwindow* getWindow()
		/*
		* returns the window pointer
		*/
		GLFWwindow* getWindow() { return m_window; }

		///void start(int w, int h, DEngine::InputManager& im)
		/*
		* method for initialising the whole program
		*/
		void start(int w, int h, DEngine::InputManager& im);
	private:
		GLFWwindow* m_window;

	};

}