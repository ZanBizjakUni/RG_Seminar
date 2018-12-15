#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <memory>

#include <DProps.h>
#include <InputManager.h>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	//methods
	void systemInit();
	void setCallbacks();
	void controlManager();
	void gameLoop();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);

	//variables
	GLFWwindow* window;
	DEngine::InputManager m_inputManager;
	const unsigned int m_width;
	const unsigned int m_height;
	float m_vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

};

