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
	if (m_inputManager.isKeyPressed(GLFW_KEY_F1)) {
		m_rooms.back().selectFirstWall();
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

	if (m_inputManager.isKeyPressed(GLFW_KEY_E)) {
		if (m_collisionManager.pointCollision(m_player->getLookingAt(), m_door.getMinAABB(), m_door.getMaxAABB())) {
			m_door.openClose();
		}
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
		std::ofstream file("test.lvl", std::ios::out | std::ios::binary);
		for (auto& it : m_rooms) {
			it.writeToFile(file);
		}
		file.close();
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_Z)) {
		m_square.rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (m_inputManager.isKeyPressed(GLFW_KEY_U)) {
		m_square.translate(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	if (m_inputManager.isKeyPressed(GLFW_KEY_I)) {
		m_square.translate(glm::vec3(0.0f, 0.0f, -1.0f));
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

	/*INITIALISING OBJECTS*/
	m_square = TexturedEntity("square", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	m_square.setTexBind("textures/awesomeface.png");
	//m_square.setTexBind("textures/wall.jpg");

	m_enemy = Enemy("skeleton", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	m_enemy.setTexBind("textures/skeleton.png");

	m_door = Door("square", glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f));
	m_door.setTexBind("textures/door.png");

	m_light = Entity("cube", glm::vec4(1.0f, 0.75f, -2.0f, 1.0f));
	
	m_square.setRootEntity();
//	m_square.setChildren(&m_light);

	m_rooms.emplace_back(Room(glm::vec3(0.0f, 0.0f, 0.0f), m_player));
	//m_rooms.back().addWall(Orientation::FLOOR);
	//m_rooms.back().addLight();

	//m_shader->use();
	m_shaders["shader"]->use();
	/*for (int i = 0; i < m_binder.getTextureSize(); i++) {
		//m_shader->set1i("texture" + std::to_string(i), i);
		m_shaders["shader"]->set1i("texture" + std::to_string(i), i);
	}*/
	m_shaders["shader"]->set1i("texture" + std::to_string(1), 0);

//	m_shader->unuse();
	m_shaders["shader"]->unuse();
	//m_player->init();
}

///draw()
/*
* Draws all elements of the program
*/
void MainGame::draw() {
	
}

///gameLoop()
/*
* Main game loop, loops around until said otherwise
*/


/*
if (it.isTextureless()) {
				m_texturelessShader->use();
				m_texturelessShader->setMat4fv("view", m_player->returnView());
				m_texturelessShader->setMat4fv("projection", m_player->returnProjection());
				m_texturelessShader->setMat4fv("model", it.returnTransMat());
				m_texturelessShader->set3f("uColor", it.getColor());
			}
			else {
				m_shader->use();
				m_shader->setMat4fv("view", m_player->returnView());
				m_shader->setMat4fv("projection", m_player->returnProjection());
				m_shader->setMat4fv("model", it.returnTransMat());
				m_shader->set3f("lightColor", m_lights[0].getColor());
				m_shader->set3fv("lightPos", lightsPos);
				m_shader->setMat3fv("normModel", it.getNormModel());
				m_shader->set3f("viewPos", m_player->getPos());
				m_shader->set1i("arrSize", (GLint)m_lights.size());
			}
			it.draw(m_binder);
*/
	
void MainGame::gameLoop(){
	/*Stuff to reorganise in project ( following the tutorial )*/
	
	/*Stuff to reorganise ^*/
	std::vector<glm::vec3> lightsPos;
	
	while (!glfwWindowShouldClose(m_ignition.getWindow())) {
		DEngine::beginTime = glfwGetTime();
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		/*TODO: reorganise the code below*/
		//m_square.rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		/*m_lightSourceShader->use();
		m_lightSourceShader->setMat4fv("model", m_light.returnTransMat());
		m_lightSourceShader->setMat4fv("view", m_player->returnView());
		m_lightSourceShader->setMat4fv("projection", m_player->returnProjection());
		m_lightSourceShader->set3f("lightColor", m_light.getColor());*/

		/*m_shaders["lightSource"]->use();
		m_shaders["lightSource"]->setMat4fv("model", m_light.returnTransMat());
		m_shaders["lightSource"]->setMat4fv("view", m_player->returnView());
		m_shaders["lightSource"]->setMat4fv("projection", m_player->returnProjection());
		m_shaders["lightSource"]->set3f("lightColor", m_light.getColor());

	//	m_light.draw(m_binder);
	*/
	/*	m_shaders["shader"]->use();
		m_shaders["shader"]->setMat4fv("model", m_square.returnTransMat());
		m_shaders["shader"]->setMat4fv("view", m_player->returnView());
		m_shaders["shader"]->setMat4fv("projection", m_player->returnProjection());
		m_shaders["shader"]->setMat3fv("normModel", m_square.getNormModel());
		m_shaders["shader"]->set3f("lightColor", m_light.getColor());
		m_shaders["shader"]->set3f("viewPos", m_player->getPos());
		m_shaders["shader"]->set3f("lightPos", m_light.getPos());
		m_shaders["shader"]->set1i("arrSize", 1);*/

		/*m_shader->use();
		m_shader->setMat4fv("model", m_square.returnTransMat());
		m_shader->setMat4fv("view", m_player->returnView());
		m_shader->setMat4fv("projection", m_player->returnProjection());
		m_shader->setMat3fv("normModel", m_square.getNormModel());
		m_shader->set3f("lightColor", m_light.getColor());
		m_shader->set3f("viewPos", m_player->getPos());
		m_shader->set3f("lightPos", m_light.getPos());
		m_shader->set1i("arrSize", 1);*/
//		m_shaders["shader"]->set3f("worldSpace", m_square.getPos());

	/*	m_square.draw(m_binder);

		m_shaders["shader"]->setMat4fv("model", m_door.returnTransMat());
		m_shaders["shader"]->setMat4fv("projection", m_player->returnProjection());
		m_shaders["shader"]->setMat3fv("normModel", m_door.getNormModel());
		m_door.draw(m_binder);
		*/
		for (auto &it : m_rooms) {
			it.drawWalls(m_binder, m_shaders["shader"]);

			it.drawLights(m_binder, m_shaders["lightSource"]);

			it.drawDoors(m_binder, m_shaders["shader"]);
		}
		m_shaders["billboard"]->use();
		m_shaders["billboard"]->setMat4fv("model", m_enemy.returnTransMat());
		m_shaders["billboard"]->setMat4fv("view", m_player->returnView());
		m_shaders["billboard"]->setMat4fv("projection", m_player->returnProjection());
		m_shaders["billboard"]->setMat3fv("normModel", m_enemy.getNormModel());
		m_shaders["billboard"]->set3f("worldSpace", m_enemy.getPos());
		m_shaders["billboard"]->set3f("lightColor", m_light.getColor());
		m_shaders["billboard"]->set3f("viewPos", m_player->getPos());
		m_shaders["billboard"]->set3f("lightPos", m_light.getPos());
		m_shaders["billboard"]->set2f("UV", m_enemy.getTexCoord());
		m_shaders["billboard"]->set2f("offset", m_enemy.getOffset());
	//	m_shaders["billboard"]->set1i("arrSize", 1);

		m_enemy.draw(m_binder);
		m_enemy.update();
		/*********************************/
		glfwPollEvents();
		controlManager();
	//	m_player->setBack(m_collisionManager.checkCollision(m_player->getMinAABB(), m_player->getMaxAABB(), m_square.getMinAABB(), m_square.getMaxAABB()));
		m_rooms.back().wallColider();
		m_player->update(m_inputManager.getCordsOffset());
		m_inputManager.update();
		//printf_s("%d\n", m_collisionManager.checkCollision(m_player->getPos(), m_square.getMinAABB(), m_square.getMaxAABB()));

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
