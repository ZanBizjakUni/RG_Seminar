#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "GenericStuff.h"
#include "ShadersComp.h"
#include "SpriteBatch.h"


class MainGame;
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
private:
	void systemInit();
	void shadersInit();
	void levelInit();
	void setCallbacks();
	void gameLoop();
	void gameRender();

	GameState m_gameState;
	GLFWwindow* window;
	PlayingGround::ShadersComp m_colorProgram;
	PlayingGround::SpriteBatch m_triangle;

	const int m_width;
	const int m_height;
	bool loop = false;
};

