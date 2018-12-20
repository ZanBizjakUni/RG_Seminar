#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <memory>
#include <array>
#include <vector>
#include <random>

#include <DProps.h>
#include <InputManager.h>
#include <ShadersComp.h>
#include <Ignition.h>
#include <Camera.h>

#include "TexturedEntity.h"
#include "Player.h"
class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	//methods
	void systemInit();
	void setShaders();
	void setCallbacks();
	void controlManager();
	void enviromentInit();
	void draw();
	void gameLoop();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	//variables
	DEngine::Ignition m_ignition;
	DEngine::InputManager m_inputManager;
	const unsigned int m_width;
	const unsigned int m_height;

	/*TODO: Proper implementation of bottom attributes*/
	DEngine::ShadersComp* m_shader;
	DEngine::Binder m_binder;
	TexturedEntity m_square;
	std::vector<TexturedEntity> m_cubes;
	Player* m_player;

};

