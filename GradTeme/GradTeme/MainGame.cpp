#include "MainGame.h"
#include <PlayingGround\ErrorMsg.h>
#include <iostream>
#include <math.h>
MainGame::MainGame() :
	m_gameState(GameState::MENU),
	m_width(1024),
	m_height(800),
	m_currTime(0),
	m_prevTime(0)
{

}

MainGame::~MainGame()
{
	glfwTerminate();
}





void MainGame::run() {
	systemInit();
	shadersInit();
	setCallbacks();
	levelInit();
	gameLoop();
}

void MainGame::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode){
	PlayingGround::InputManager* m_inputManager = reinterpret_cast<PlayingGround::InputManager*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);

	}

	if (action == GLFW_PRESS) {
		m_inputManager->pressKey(key);
	}
	if (action == GLFW_RELEASE) {
		m_inputManager->releaseKey(key);
	}

	
}

void MainGame::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods){
	PlayingGround::InputManager* m_inputManager = reinterpret_cast<PlayingGround::InputManager*>(glfwGetWindowUserPointer(window));


	if (action == GLFW_PRESS) {
		m_inputManager->pressKey(button);
	}
	if (action == GLFW_RELEASE) {
		m_inputManager->releaseKey(button);
	}
}

void MainGame::mousePosCallback(GLFWwindow * window, double xPos, double yPos){
	PlayingGround::InputManager* m_inputManager = reinterpret_cast<PlayingGround::InputManager *>(glfwGetWindowUserPointer(window));
	m_inputManager->setMouseCords(xPos, yPos);
	glm::vec3 front;
	glm::vec2 offset = m_inputManager->getCordsOffset();
	offset.y *= -1;
	offset *= GameThings::sensitivity;

	GameThings::yaw += offset.x;
	GameThings::pitch+= offset.y;

	if (GameThings::pitch > 89.0f) {
		GameThings::pitch = 89.0f;
	}
	if (GameThings::pitch < -89.0f) {
		GameThings::pitch = -89.0f;
	}

	front.x = cos(glm::radians(GameThings::pitch)) * cos(glm::radians(GameThings::yaw));
	front.y = sin(glm::radians(GameThings::pitch));
	front.z = cos(glm::radians(GameThings::pitch)) * sin(glm::radians(GameThings::yaw));
	GameThings::cameraFront = glm::normalize(front);
	GameThings::prevYaw = GameThings::yaw;
}

void MainGame::systemInit() {
	//inicializacija glfw okna
	glfwInit();
	if (!glfwInit()) {
		PlayingGround::ErrorMsg::message("cannot init glfw \n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//deklaracija okna (width, height, imeOkna, ali bo fullscreen ali ne, ali bo okno delilo resource ali ne)
	window = glfwCreateWindow(GameThings::width, GameThings::height, "grad teme", nullptr, nullptr);
	if (window == nullptr) { //v primeru da se okno ne more ustvariti
		PlayingGround::ErrorMsg::message("Cannot create window");
		glfwTerminate();
		m_gameState = GameState::EXIT;
	}
	glfwMakeContextCurrent(window);
	//	std::cout << glGetString(GL_VERSION);
	//inicializacija knjižnice glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) { // v primeru èe se ne more inicializirat
		PlayingGround::ErrorMsg::message("Cannot init glew \n");
		std::cout << glewGetErrorString(err) << "\n";
		m_gameState = GameState::EXIT;
	}

	glfwSetWindowUserPointer(window, &m_inputManager);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	/*
	glfw okno ima koordinate narejene od -1 od 1 (iz leve proti desni.
	Tu dosežemo "normalizacijo" koordinat tako da bo program koordinate
	gledal od 0 do nastavljene velikosti (npr. v oknu 800x600 bo koordinata
	-0.5,0.5 transformiran na 200,450
	*/

	glfwGetFramebufferSize(window, (int*)&m_width, (int*)&m_height);
	glViewport(0, 0, GameThings::width, GameThings::height);
	
	//m_camera.init();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void MainGame::shadersInit() {
	printf("compiling colorShader...");
	m_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	m_colorProgram.linkShaders();
	printf("compiling complete!\ncompiling lightingShader...");
	m_lightingProgram.compileShaders("shaders/lightingShader.vert", "shaders/lightingShader.frag");
	m_lightingProgram.linkShaders();
	printf(" compiling complete!\n compiling enemyShader...");

	m_enemyProgram.compileShaders("shaders/tempShader.vert", "shaders/tempShader.frag");
	m_enemyProgram.linkShaders();
	printf("compiling complete! \n");

	m_menuProgram.compileShaders("shaders/menuShader.vert", "shaders/menuShader.frag");
	m_menuProgram.linkShaders();

//	m_swordProgram.compileShaders("shaders/swordShader.vert", "shaders/swodShader.frag");
//	m_menuProgram.linkShaders();

	
	GameThings::chID = m_colorProgram.returnProgramID();
}

void MainGame::levelInit() {
	m_level = new Level(m_floorCeil, m_northSouth, m_eastWest, m_EWDoors, m_SNDoors);
	m_player = new Player;
	m_player->init(m_level->getSP());
	m_enemy = new Enemy;
	m_enemy->init(m_player->getPos(), m_enemyProgram.returnProgramID());
	m_end = new kocka;
	m_end->init(m_colorProgram.returnProgramID(), m_level->getEP());
	m_end->indentify(Side::FLOOR);
	m_floorCeil.emplace_back();
	m_floorCeil.back().init(m_colorProgram.returnProgramID(), m_level->getEP());
	m_floorCeil.back().indentify(Side::CEIL);
	m_collision = new Collision;
	m_collision->init(m_eastWest, m_northSouth);
	m_enemies.clear();
//	m_sword = new Sword;
//	m_sword->init(m_swordProgram.returnProgramID(), (m_player->getPos() + glm::vec3(0.0f,0.0f,-1.0f)));
	m_light.emplace_back();
	m_light[0].init(m_lightingProgram.returnProgramID());
	//m_light.changeActivnes(false);
//	m_swordSpriteBatch.init("sword.png", m_sword->getVerts(), true);
	m_startSpriteBatch.init("start.png", m_menu.getVerts(), true);
	m_exitSpriteBatch.init("exit.png", m_menu.getVerts(), true);
	m_enemySpriteBatch.init("ghost.png", m_enemy->getVerts(), true);
	m_endSpriteBatch.init("staircase.png", m_end->getVerts(), true);
	m_doorEWSpriteBatch.init("door.png", m_EWDoors[0].getVerts(),true);
	m_doorNSSpriteBatch.init("door.png", m_SNDoors[0].getVerts(), true);
	m_floorCeilSpriteBatch.init("brick_wall.png", m_floorCeil[0].getVerts(), true);
	m_northSouthSpriteBatch.init("brick_wall.png", m_northSouth[0].getVerts(), true);
	m_eastWestSpriteBatch.init("brick_wall.png", m_eastWest[0].getVerts(), true);
	m_lightSpriteBatch.init("container_org.jpg", m_light[0].getVerts(), false);
}

//funkcija za nastavljanje callbackov ( inputi tipkovnice, miske, itd.)
void MainGame::setCallbacks() {
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
}
float rotVal = 0.01;
float rotSum = 0;
void MainGame::gameLoop() {
	while (!glfwWindowShouldClose(window)) {
		m_currTime = glfwGetTime();
		GameThings::deltaTime = m_currTime - m_prevTime;
		m_inputManager.update();
		glfwPollEvents();
		if (m_inputManager.isKeyPressed(GLFW_KEY_U)) {
			m_gameState = GameState::GAMEPLAY;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			levelInit();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_B)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			m_gameState = GameState::MENU;
		}
		if (m_gameState == GameState::GAMEPLAY) {
			m_player->update(m_inputManager, m_colorProgram.returnProgramID(), m_collision);
			//	m_enemy->update(m_player->getPos(), m_player->returnPrevPos(), m_collision);
	//		m_sword->update();

			if (m_level->isInRoom(m_player->returnLookAt())) {
				spawnEnemies();
				printf("isInRoom\n");
			}

			for (auto &it : m_enemies) {
				it.update(m_player->getPos(), m_player->returnPrevPos(), m_collision);
				if (glm::distance(it.returnPosition(), m_player->getPos()) <= 0.2f) {
					m_gameState = GameState::MENU;
				}
			}

			for (auto &it : m_floorCeil) {
				it.update(m_inputManager);
			}
			for (auto &it : m_northSouth) {
				it.update(m_inputManager);
			}
			for (auto &it : m_eastWest) {
				it.update(m_inputManager);
			}
			for (auto &it : m_light) {
				it.update(m_inputManager);
			}
			for (auto &it : m_EWDoors) {
				it.update(m_inputManager);
			}
			for (auto &it : m_SNDoors) {
				it.update(m_inputManager);
			}
			m_end->update(m_inputManager);

			controlCheck();

		}
		if (m_gameState == GameState::MENU) {
		}
		gameRender();
		m_prevTime = m_currTime;

	}

}

void MainGame::gameRender() {

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_gameState == GameState::GAMEPLAY) {

		//	glActiveTexture(GL_TEXTURE0);

		m_colorProgram.use();
		for (auto &it : m_floorCeil) {
			it.draw(m_floorCeilSpriteBatch, m_colorProgram.returnProgramID(),/* m_light[0].returnPosition()*/ glm::vec3(1.0f, 1.5f, 0.0f));
		}
		for (auto &it : m_northSouth) {
			it.draw(m_northSouthSpriteBatch, m_colorProgram.returnProgramID(), glm::vec3(1.0f, 1.5f, 0.0f));
		}
		for (auto &it : m_eastWest) {
			it.draw(m_eastWestSpriteBatch, m_colorProgram.returnProgramID(), glm::vec3(1.0f, 1.5f, 0.0f));
		}
		for (auto &it : m_EWDoors) {
			it.draw(m_doorEWSpriteBatch, m_colorProgram.returnProgramID(), glm::vec3(1.0f, 1.5f, 0.0f));
		}
		for (auto &it : m_SNDoors) {
			it.draw(m_doorNSSpriteBatch, m_colorProgram.returnProgramID(), glm::vec3(1.0f, 1.5f, 0.0f));
		}
		m_end->draw(m_endSpriteBatch, m_colorProgram.returnProgramID(), glm::vec3(1.0f, 1.5f, 0.0f));


		m_enemyProgram.use();
		for (auto &it : m_enemies) {
			it.draw(m_enemySpriteBatch, m_enemyProgram.returnProgramID());
		}
		//	m_enemy->draw(m_enemySpriteBatch, m_enemyProgram.returnProgramID());
	//	m_swordProgram.use();
	//	m_sword->draw(m_swordSpriteBatch);
	}
	if (m_gameState == GameState::MENU) {
		m_menuProgram.use();
		m_menu.drawS(m_startSpriteBatch, m_menuProgram.returnProgramID());
		m_menu.drawE(m_endSpriteBatch, m_menuProgram.returnProgramID());
	}
	glfwSwapBuffers(window);
}

void MainGame::spawnEnemies(){
	glm::vec3 spawn;
	int x, z, w, h;
	for (size_t i = 0; i < 2; i++) {
		x = m_level->returnCurrRoom().x;
		z = m_level->returnCurrRoom().z;
		w = m_level->returnCurrRoom().sizeX;
		h = m_level->returnCurrRoom().sizeY;
		spawn.x = (i + x + (w / 2)) * 2.0f;
		spawn.y = 1.0f;
		spawn.z = (z + (h / 2)) * 2.0f;
		printf("spawn: %g %g player: %g %g\n", spawn.x, spawn.z, m_player->getPos().x, m_player->getPos().z);

		m_enemies.emplace_back();
		m_enemies.back().init(spawn, m_enemyProgram.returnProgramID());
	}
}
GLfloat MainGame::testFunc(GLfloat a){
	a *= 10;
	int b = roundf(a);

	return (GLfloat)b/10;
}

bool MainGame::checkPos(glm::vec3 a, glm::vec3 b) {
	if (a.x > b.x - 1 && a.x < b.x + 1) {
		if (a.y > b.y - 1 && a.y < b.y + 1) {
			if (a.z > b.z - 1 && a.z < b.z + 1) {
				return true;
			}
		}
	}
	return false;
}

void MainGame::controlCheck(){
	if (m_inputManager.isKeyPressed(GLFW_KEY_E)) {
		for (auto &it : m_EWDoors) {
			if (checkPos(m_player->returnLookAt(), it.returnPosition())) {
				it.rotate();
				//it.changeActivnes(false);
			}
		}
		for (auto &it : m_SNDoors) {
			if (checkPos(m_player->returnLookAt(), it.returnPosition())) {
				it.rotate();
			}
		}
		if (checkPos(m_player->returnLookAt(), m_end->returnPosition())) {
			levelInit();
		}
	}

	if (m_inputManager.isKeyPressed(GLFW_MOUSE_BUTTON_1)) {
		for (auto &it : m_enemies) {
			if (checkPos(m_player->returnLookAt(), it.returnPosition())) {
				it.getHit();
				if (it.isDead()) {
					it = m_enemies.back();
					m_enemies.pop_back();
				}
			}
		}
	}
}


