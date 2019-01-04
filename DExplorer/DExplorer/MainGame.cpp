#include "MainGame.h"

///MainGame()
/*
* Constructor for MainGameObject.
* Setting up initial width and height.
*/
MainGame::MainGame() : m_width(800),
					   m_height(600)				   

					   
{
	DEngine::setHeight(m_height);
	DEngine::setWidth(m_width);
}


MainGame::~MainGame()
{

}

///start()
/*
* Function that sets up the whole program.
* Calls the initial setup functions
*/
void MainGame::start(){
	 
	systemInit();
	setShaders();
	setCallbacks();	
	enviromentInit();
	gameLoop();

}



///systemInit()
/*
* Initialises GLFW and GLAD
* Creates the window context 
* Sets up Viewport.
*/
void MainGame::systemInit() {
	m_ignition.start(m_width, m_height, m_inputManager);
	/*m_shader = new DEngine::ShadersComp();
	m_texturelessShader = new DEngine::ShadersComp();
	m_lightSourceShader = new DEngine::ShadersComp();
	m_billboardShader = new DEngine::ShadersComp();*/

	m_shaders["shader"] = new DEngine::ShadersComp();
	m_shaders["textureless"] = new DEngine::ShadersComp();
	m_shaders["lightSource"] = new DEngine::ShadersComp();
	m_shaders["billboard"] = new DEngine::ShadersComp();

	m_player = new Player();
	

}
///setShaders()
/*
* Compile and link ShaderComp objects defined in MainGame class
*/
void MainGame::setShaders() {
	/*m_shader->compileShaders("shaders/shader.vert", "shaders/shader.frag");
	m_shader->linkShaders();

	m_texturelessShader->compileShaders("shaders/lighting.vert", "shaders/textureless.frag");
	m_texturelessShader->linkShaders();

	m_lightSourceShader->compileShaders("shaders/lightsource.vert", "shaders/lightsource.frag");
	m_lightSourceShader->linkShaders();

	m_billboardShader->compileShaders("shaders/billboard.vert", "shaders/shader.frag");
	m_billboardShader->linkShaders();*/

	m_shaders["shader"]->compileShaders("shaders/shader.vert", "shaders/shader.frag");
	m_shaders["shader"]->linkShaders();

	m_shaders["textureless"]->compileShaders("shaders/lighting.vert", "shaders/textureless.frag");
	m_shaders["textureless"]->linkShaders();

	m_shaders["lightSource"]->compileShaders("shaders/lightsource.vert", "shaders/lightsource.frag");
	m_shaders["lightSource"]->linkShaders();

	m_shaders["billboard"]->compileShaders("shaders/billboard.vert", "shaders/enemy.frag");
	m_shaders["billboard"]->linkShaders();

}

///setCallBacks()
/*
* Link certain functions from this class to the window context event listener
*/
void MainGame::setCallbacks() {

	//set callback for when window is resized
	glfwSetFramebufferSizeCallback(m_ignition.getWindow(), framebuffer_size_callback);
	//set callback for when a key is pressed
	glfwSetKeyCallback(m_ignition.getWindow(), keyCallback);

	glfwSetCursorPosCallback(m_ignition.getWindow(), mouseCallback);

	glfwSetMouseButtonCallback(m_ignition.getWindow(), mouseButtonCallback);
}

///controlManager()
/*
* Contains controls of the program
*/
void MainGame::controlManager() {
	//if escape is pressed close the glfw window
	if (m_inputManager.isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(m_ignition.getWindow(), true);
	}

	if (m_inputManager.isKeyPressed(GLFW_KEY_F3)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_F4)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (m_inputManager.isKeyDown(GLFW_KEY_A)) {
		m_player->move(Direction::LEFT);
	}
	
	if (m_inputManager.isKeyDown(GLFW_KEY_D)) {
		//m_square.rotate(-1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		m_player->move(Direction::RIGHT);
	}
	if (m_inputManager.isKeyDown(GLFW_KEY_W)) {
		m_player->move(Direction::FORWARD);
	}
	if (m_inputManager.isKeyDown(GLFW_KEY_S)) {
		m_player->move(Direction::BACKWARD);
	}
	if (m_inputManager.isKeyDown(GLFW_KEY_LEFT_SHIFT)) {
		m_player->toggleSprint();
	}
	else {
		m_player->unToggleSprint();
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_SPACE)) {
		m_player->jump();
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_E)) {
		if (m_player->getState() == PState::PLAY) {
			for (int i = 0; i < m_rooms.size(); i++) {
				m_rooms[i].checkDoors();
			}
		}
	}
	if (m_inputManager.isKeyPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		if (m_player->getState() == PState::PLAY) {
			for (int i = 0; i < m_rooms.size(); i++) {
				m_rooms[i].checkEnemies();
			}
		}
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_F10)) {
		m_player->setState(PState::CREATE);
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_F9)) {
		m_player->setState(PState::PLAY);
	}

	if (m_player->getState() == PState::CREATE) {
		if (m_inputManager.isKeyPressed(GLFW_KEY_1)) {
			m_rooms.back().selectFirstWall();
		}

		if (m_inputManager.isKeyPressed(GLFW_KEY_2)) {
			m_rooms.back().selectFirstLight();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_3)) {
			m_rooms.back().selectFirstDoor();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_4)) {
			m_rooms.back().selectFistEnemy();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_5)) {
			m_rooms.back().unselectAll();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_0)) {
			m_rooms.emplace_back(Room(m_rooms.back().getLastDoorPos(), m_player));
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_KP_ADD)) {
			DEngine::precision += 0.1f;
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_KP_SUBTRACT)) {
			DEngine::precision -= 0.1f;
		}


		if (m_inputManager.isKeyPressed(GLFW_KEY_N)) {
			m_rooms.back().addWall(WallType::FLOOR);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_M)) {
			m_rooms.back().addWall(WallType::WALL);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_R)) {
			m_rooms.back().rotateSelected();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_L)) {
			m_rooms.back().addLight();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_B)) {
			m_rooms.back().addDoor();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_P)) {
			m_rooms.back().addEnemy();
		}

		if (m_inputManager.isKeyPressed(GLFW_KEY_INSERT)) {
			m_rooms.back().selectNext();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_HOME)) {
			m_rooms.back().selectPrev();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_DELETE)) {
			m_rooms.back().delSelected();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_F5)) {
			std::ofstream file("test.lvl", std::ios::out | std::ios::binary | std::ios::trunc);
			printf_s("Saving level...\n");
			int tmp;
			tmp = m_rooms.size();
			file.write((char*)&tmp, sizeof(int));
			for (auto& it : m_rooms) {
				it.writeToFile(file);
			}
			printf_s("Save complete!\n");
			file.close();
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_LEFT)) {
			m_rooms.back().moveSelected(Move::LEFT);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_RIGHT)) {
			m_rooms.back().moveSelected(Move::RIGHT);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_UP)) {
			m_rooms.back().moveSelected(Move::FORWARD);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_DOWN)) {
			m_rooms.back().moveSelected(Move::BACKWARD);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_PAGE_UP)) {
			m_rooms.back().moveSelected(Move::UP);
		}
		if (m_inputManager.isKeyPressed(GLFW_KEY_PAGE_DOWN)) {
			m_rooms.back().moveSelected(Move::DOWN);
		}

	}


}

void MainGame::enviromentInit() {
	m_binder.setBinder("square", {
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,0.0f,  0.0f, 1.0f,// top right
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,0.0f,  0.0f, 1.0f,// bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,0.0f,  0.0f, 1.0f,// bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,0.0f,  0.0f, 1.0f// top left 
					   },
	 { 3, 2, 3 },
	 {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	 });

	m_binder.setBinder("skeleton", {
	 0.25f,  0.5f, 0.0f, 0.1f, 0.2f, 0.0f,  0.0f, 1.0f,// top right
	 0.25f, -0.5f, 0.0f, 0.1f, 0.0f, 0.0f,  0.0f, 1.0f,// bottom right
	-0.25f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,// bottom left
	-0.25f,  0.5f, 0.0f, 0.0f, 0.2f, 0.0f,  0.0f, 1.0f// top left 
					   },
					   { 3, 2, 3 },
	 {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	 });
	m_binder.setBinder("cube", {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,-1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
					   },
					   { 3, 2, 3 });

	m_binder.setBinder("normalCube", {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
					   },
						{ 3, 3 });



	m_binder.setTextureBinder("textures/stonebricks1.jpg");
	m_binder.setTextureBinder("textures/container.jpg");
	m_binder.setTextureBinder("textures/awesomeface.png");
	m_binder.setTextureBinder("textures/wall.jpg");
	m_binder.setTextureBinder("textures/skeleton.png");
	m_binder.setTextureBinder("textures/door.png");
	m_binder.setTextureBinder("textures/stonefloor.jpg");
	m_binder.setTextureBinder("textures/stonewall.png");

	/*INITIALISING OBJECTS*/

	//m_rooms.emplace_back(Room(glm::vec3(0.0f, 0.0f, 0.0f), m_player));
	std::ifstream file("test.lvl");
	int tmp;
	file.read((char*)&tmp, sizeof(int));
	for (int i = 0; i < tmp; i++) {
		m_rooms.emplace_back(Room(file, m_player));
	}
	file.close();

	m_shaders["shader"]->use();

	m_shaders["shader"]->set1i("texture" + std::to_string(1), 0);

//	m_shader->unuse();
	m_shaders["shader"]->unuse();
	//m_player->init();

	printf_s("EDIT MODE CONTROLS:\n");
	printf_s("Spawn Wall: M\nSpawn Floor\nSpawn Door: B\nSpawn Enemy: P\nSpawn lightsource(32 max): L\n");
	printf_s("Use arrow keys to move the selected object around(red shade)\n PgUp and PgDown for moving objects up and down\n");
	printf_s("Home: select next object of the selected type\nInsert: Select previous object of the selected type\n");
	printf_s("1: Select the first wall/floor object\n2: Select first light\n3: select first door\n4: Select first enemy\n");
}

///gameLoop()
/*
* Main game loop, loops around until said otherwise
*/	
void MainGame::gameLoop(){
	
	
	while (!glfwWindowShouldClose(m_ignition.getWindow())) {
		DEngine::beginTime = glfwGetTime();
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		m_currRoom = -1;
		if (m_player->getState() == PState::PLAY) {
			for (int i = 0; i < m_rooms.size(); i++) {
				if (m_collisionManager.checkCollision(m_player->getMinAABB(), m_player->getMaxAABB(), m_rooms[i].getMinPos(), m_rooms[i].getMaxPos()) != -1) {
					m_rooms[i].drawWalls(m_binder, m_shaders["shader"]);
					m_rooms[i].drawLights(m_binder, m_shaders["lightSource"]);
					m_rooms[i].drawDoors(m_binder, m_shaders["shader"]);
					m_rooms[i].drawEnemies(m_binder, m_shaders["billboard"]);
					
				}
			}
		}
		if (m_player->getState() == PState::CREATE) {
			for (auto &it : m_rooms) {

				it.drawWalls(m_binder, m_shaders["shader"]);

				it.drawLights(m_binder, m_shaders["lightSource"]);

				it.drawDoors(m_binder, m_shaders["shader"]);

				it.drawEnemies(m_binder, m_shaders["billboard"]);
			}
		}
		else {
			
		}
		

		/*********************************/
		glfwPollEvents();
		controlManager();
		m_player->gravity();
		if (m_player->getState() == PState::PLAY) {
			for (int i = 0; i < m_rooms.size(); i++) {
				if (m_collisionManager.checkCollision(m_player->getMinAABB(), m_player->getMaxAABB(), m_rooms[i].getMinPos(), m_rooms[i].getMaxPos()) != -1) {
					m_rooms[i].wallColider();
				}
			}
		}
		
		m_player->update(m_inputManager.getCordsOffset());
		m_inputManager.update();
		m_player->setPrevPos();
		//printf_s("%d \r", m_collisionManager.checkCollision(m_player->getMinAABB(), m_player->getMaxAABB(), m_rooms.back().getMinPos(), m_rooms.back().getMaxPos()));
		glfwSwapBuffers(m_ignition.getWindow());
		DEngine::endTime = glfwGetTime();
		DEngine::setDelta();
	}
}


///framebuffer_size_callback(GLFW* window, int width, int height)
/*
* The callback function that gets called everytime the window gets resized
*/
void MainGame::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	//set the viewport to a new value, since the window has been resized
	glViewport(0, 0, width, height);

	//get the input manager from the window user pointer and recast it to a pointer
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));

	//set the new width and height via the input manager
	m_inputManager->setNewWH(height, width);
}

///keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
/*
* The callback function that gets called everytime a key gets pressed 
*/
void MainGame::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	//get the input manager from the window user pointer and recast it to a pointer

	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));

	//if a key gets pressed set its value in the input managers key map to true
	if (action == GLFW_PRESS) {
		m_inputManager->pressKey(key);
	}

	//if it gets relesed set it to false
	if (action == GLFW_RELEASE) {
		m_inputManager->releaseKey(key);
	}


}

void MainGame::mouseCallback(GLFWwindow * window, double xpos, double ypos) {
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));
	m_inputManager->setMouseCords(xpos, ypos);

}

void MainGame::mouseButtonCallback(GLFWwindow * window, int button, int action, int mods) {
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));


	if (action == GLFW_PRESS) {
		m_inputManager->pressKey(button);
	}
	if (action == GLFW_RELEASE) {
		m_inputManager->releaseKey(button);
	}
}
