#include "MainGame.h"


MainGame::MainGame() : m_width(800),
					   m_height(600)
{
	
}


MainGame::~MainGame()
{

}

void MainGame::start(){
	 
	systemInit();
	setCallbacks();
	gameLoop();

}




void MainGame::systemInit() {
	/*******************************************
	  *inicializacija glfw okna in nastavljanje
	  *opcij za reèeno okno (hints)
	  *******************************************/

	DEngine::setHeight(m_height);
	DEngine::setWidth(m_width);

	if (!glfwInit()) {
		printf_s("Could not initialise glfw\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(DEngine::width, DEngine::height, "DExplorer", nullptr, nullptr);

	if (window == nullptr) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf_s("Failed to initialize GLAD\n");
		return;
	}

	glfwSetWindowUserPointer(window, &m_inputManager);

	glViewport(0, 0, DEngine::width, DEngine::height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}

void MainGame::setCallbacks() {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);
}

void MainGame::controlManager() {
	if (m_inputManager.isKeyPressed(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}
}

void MainGame::gameLoop(){
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		controlManager();
		m_inputManager.update();

		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

	}
}



void MainGame::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));
	m_inputManager->setNewWH(height, width);
}

void MainGame::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));

	if (action == GLFW_PRESS) {
		m_inputManager->pressKey(key);
	}
	if (action == GLFW_RELEASE) {
		m_inputManager->releaseKey(key);
	}


}