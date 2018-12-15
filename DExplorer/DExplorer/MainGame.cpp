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

	glViewport(0, 0, m_width, m_height);

}

void MainGame::setCallbacks() {
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);
}

void MainGame::gameLoop(){
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
		m_inputManager.update();

	}
}



void MainGame::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void MainGame::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	DEngine::InputManager* m_inputManager = reinterpret_cast<DEngine::InputManager*>(glfwGetWindowUserPointer(window));

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