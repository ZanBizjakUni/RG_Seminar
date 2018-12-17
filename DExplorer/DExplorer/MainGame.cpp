#include "MainGame.h"

///MainGame()
/*
* Constructor for MainGameObject.
* Setting up initial width and height.
*/
MainGame::MainGame() : m_width(800),
					   m_height(600)
					   
{
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
	

}
///setShaders()
/*
* Compile and link ShaderComp objects defined in MainGame class
*/
void MainGame::setShaders() {
	m_shader.compileShaders("shaders/shader.vert", "shaders/shader.frag");
	m_shader.linkShaders();
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
}

void MainGame::enviromentInit() {
	m_binder.setBinder("square", {
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
					   },
	 {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	 });
	m_square = Entity("square");
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

	/*float verts[] = {
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
	};*/

	/*std::array<float, 24> verts = {
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// top right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // top left 
	};
	std::vector<float> vertices;
	vertices.insert(vertices.begin(), verts.begin(), verts.end());
	vertices.shrink_to_fit();*/
	/*unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};*/
/*
	std::vector<unsigned int> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	indices.shrink_to_fit();
	// postion attribute ( layout (location = 0) in vert shader)
	
	//initialisation of: Vertex Buffer Object, Vertex Array Object and Element Buffer Object
	unsigned int VBO, VAO, EBO;

	//generate vertex array object
	glGenVertexArrays(1, &VAO);

	//generate Vertex Buffer Object (its id)
	glGenBuffers(1, &VBO);

	//generate Element Buffer Object (its id)
	glGenBuffers(1, &EBO);

	//bind the generated VAO id
	glBindVertexArray(VAO);

	//bind VBO and EBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.capacity(), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.capacity(), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute ( layout (location = 1) in vert shader)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/

	/*Stuff to reorganise ^*/
	while (!glfwWindowShouldClose(m_ignition.getWindow())) {
		/*TODO: reorganise the code below*/
		m_shader.use();
		m_square.draw(m_binder);
		/*********************************/
		glfwPollEvents();
		controlManager();
		m_inputManager.update();

		glfwSwapBuffers(m_ignition.getWindow());
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

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