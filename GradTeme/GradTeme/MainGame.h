#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <PlayingGround\GenericStuff.h>
#include <PlayingGround\ShadersComp.h>
#include <PlayingGround\SpriteBatch.h>
#include <PlayingGround\Camera.h>
#include <PlayingGround\InputManager.h>

#include <GameThings\GlobalVariables.h>
#include <GameThings\Player.h>
#include <GameThings\kocka.h>
#include <GameThings\Light.h>
#include <GameThings\Level.h>
#include <GameThings\Enemy.h>
#include <GameThings\Collision.h>
//#include <GameThings\Sword.h>

#include "Menu.h"

class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();
private:

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void mousePosCallback(GLFWwindow* window, double xPos, double yPos);
	void systemInit();
	void shadersInit();
	void levelInit();
	void setCallbacks();
	void gameLoop();
	void gameRender();
	void spawnEnemies();
	Menu m_menu;
	GLfloat testFunc(GLfloat);
	bool checkPos(glm::vec3, glm::vec3);
	void controlCheck();
	GameState m_gameState;
	GLFWwindow* window;
	Player* m_player;
	Level* m_level;
	kocka* m_end;
	Collision* m_collision;
	Enemy* m_enemy;
//	Sword* m_sword;
	std::vector<kocka> m_SNDoors;
	std::vector<kocka> m_EWDoors;
	std::vector<kocka> m_floorCeil;
	std::vector<kocka> m_northSouth;
	std::vector<kocka> m_eastWest;
	std::vector<Light> m_light;
	std::vector<Enemy> m_enemies;
	
	PlayingGround::ShadersComp m_colorProgram;
	PlayingGround::ShadersComp m_lightingProgram;
	PlayingGround::ShadersComp m_enemyProgram;
	PlayingGround::ShadersComp m_menuProgram;
//	PlayingGround::ShadersComp m_swordProgram;

//	PlayingGround::SpriteBatch m_swordSpriteBatch;
	PlayingGround::SpriteBatch m_startSpriteBatch;
	PlayingGround::SpriteBatch m_exitSpriteBatch;
	PlayingGround::SpriteBatch m_enemySpriteBatch;
	PlayingGround::SpriteBatch m_endSpriteBatch;
	PlayingGround::SpriteBatch m_floorCeilSpriteBatch;
	PlayingGround::SpriteBatch m_northSouthSpriteBatch;
	PlayingGround::SpriteBatch m_eastWestSpriteBatch;
	PlayingGround::SpriteBatch m_lightSpriteBatch;
	PlayingGround::SpriteBatch m_doorEWSpriteBatch;
	PlayingGround::SpriteBatch m_doorNSSpriteBatch;

	PlayingGround::InputManager m_inputManager;
	
	const int m_width;
	const int m_height;
	GLfloat m_currTime;
	GLfloat m_prevTime;
	bool loop = false;
	glm::mat4 m_trans;
};

