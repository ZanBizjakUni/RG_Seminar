#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "DProps.h"
#include "InputManager.h"

class Ignition {
public:
	Ignition();
	~Ignition();
	GLFWwindow* getWindow() { return m_window; }

	void start(int w, int h, DEngine::InputManager& im);
private:
	GLFWwindow* m_window;
	
};

