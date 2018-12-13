#include "MainGame.h"
#include <iostream>
MainGame::MainGame() :
	m_gameState(GameState::GAMEPLAY),
	m_width(1024),
	m_height(800)
{

}

MainGame::~MainGame()
{
	glfwTerminate();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		
	}
}

void MainGame::run() {
	systemInit();
	shadersInit();
	levelInit();
	setCallbacks();
	gameLoop();
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
	window = glfwCreateWindow(800, 600, "grad teme", nullptr, nullptr);
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
	


	/*
	glfw okno ima koordinate narejene od -1 od 1 (iz leve proti desni.
	Tu dosežemo "normalizacijo" koordinat tako da bo program koordinate
	gledal od 0 do nastavljene velikosti (npr. v oknu 800x600 bo koordinata 
	-0.5,0.5 transformiran na 200,450
	*/

	glfwGetFramebufferSize(window, (int*)&m_width, (int*)&m_height);
	glViewport(0, 0, m_width, m_height);


}

void MainGame::shadersInit(){
	m_colorProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	m_colorProgram.linkShaders();
}

void MainGame::levelInit(){
	m_triangle.init("container_org.jpg");
}

//funkcija za nastavljanje callbackov ( inputi tipkovnice, miske, itd.)
void MainGame::setCallbacks(){
	glfwSetKeyCallback(window, keyCallback);
}

void MainGame::gameLoop() {
	while (!glfwWindowShouldClose(window) ){
		glfwPollEvents();
		gameRender();
		

	}

}

void MainGame::gameRender(){
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	m_colorProgram.use();
//	m_triangle.createVertexArray();jungle

		std::cout << m_colorProgram.returnProgramID() << "\n";
		
	m_triangle.draw(m_colorProgram.returnProgramID());
	

	glfwSwapBuffers(window);
}


