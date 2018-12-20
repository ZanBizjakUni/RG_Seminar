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
	m_shader = new DEngine::ShadersComp();
	m_player = new Player();
	

}
///setShaders()
/*
* Compile and link ShaderComp objects defined in MainGame class
*/
void MainGame::setShaders() {
	m_shader->compileShaders("shaders/shader.vert", "shaders/shader.frag");
	m_shader->linkShaders();
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
}

void MainGame::enviromentInit() {
	m_binder.setBinder("square", {
	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,// top right
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,// bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f // top left 
					   },
	 {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	 });
	m_binder.setBinder("cube", {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
					   });

	m_binder.setTextureBinder("textures/container.jpg");
	m_binder.setTextureBinder("textures/awesomeface.png");

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	for (int i = 0; i < 10; i++) {

		m_cubes.emplace_back(TexturedEntity("cube", glm::vec4(cubePositions[i], 1.0f)));
		m_cubes.back().setTexBind("textures/container.jpg");
		m_cubes.back().setTexBind("textures/awesomeface.png");
		m_cubes.back().rotate(20.0f * i, glm::vec3(1.0f, 0.3f, 0.5f));

	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-1.0f, 1.0);

	m_square = TexturedEntity("square", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	m_square.setTexBind("textures/container.jpg");
	m_square.setTexBind("textures/awesomeface.png");

	m_shader->use();
	m_shader->set1i("texture1", 0);

	m_shader->set1i("texture2", 1);
	m_shader->unuse();
	m_player->init();
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
void MainGame::gameLoop(){
	/*Stuff to reorganise in project ( following the tutorial )*/
	
	m_shader->use();
	m_square.rotate(-55.0f,glm::vec3(1.0f, 0.0f, 0.0f));

	/*Stuff to reorganise ^*/


	
	while (!glfwWindowShouldClose(m_ignition.getWindow())) {
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

		/*TODO: reorganise the code below*/
		m_shader->use();
		//m_square.rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		m_player->update(m_inputManager.getCordsOffset());
		m_shader->setMat4fv("view", m_player->returnView());
		m_shader->setMat4fv("projection", m_player->returnProjection());
		for (auto& it : m_cubes) {
			m_shader->setMat4fv("model", it.returnTransMat());
			it.draw(m_binder);
		}
		//m_square.draw(m_binder);
		/*********************************/
		m_inputManager.update();
		glfwPollEvents();
		controlManager();

		glfwSwapBuffers(m_ignition.getWindow());

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
