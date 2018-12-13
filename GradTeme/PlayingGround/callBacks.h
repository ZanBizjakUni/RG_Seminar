#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace PlayingGround {

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (key = GLFW_KEY_ESCAPE && GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	void setCallBacks(GLFWwindow* window) {
		glfwSetKeyCallback(window, keyCallback);
	}



} //namespace