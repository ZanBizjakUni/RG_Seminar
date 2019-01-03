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
#include <CollisionManager.h>

#include "Player.h"
#include "Room.h"
#include "Enemy.h"
#include "Door.h"
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
	static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
	//variables
	DEngine::Ignition m_ignition;
	DEngine::InputManager m_inputManager;
	const unsigned int m_width;
	const unsigned int m_height;

	/*TODO: Proper implementation of bottom attributes*/
	DEngine::ShadersComp* m_shader;
	DEngine::ShadersComp* m_texturelessShader;
	DEngine::ShadersComp* m_lightSourceShader;
	DEngine::ShadersComp* m_billboardShader;
	std::unordered_map<std::string, DEngine::ShadersComp*> m_shaders;
	DEngine::Binder m_binder;
	std::vector<Entity> m_lights;
	Entity m_light;
	std::vector<TexturedEntity> m_cubes;
	TexturedEntity m_square;
	std::vector<Room> m_rooms;
	DEngine::CollisionManager m_collisionManager;
	Player* m_player;
	Enemy m_enemy;
	Door m_door; 
	Wall m_wall;
	int m_currRoom;

};

