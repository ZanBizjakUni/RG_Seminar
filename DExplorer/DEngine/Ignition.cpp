#include "Ignition.h"



Ignition::Ignition() {}


Ignition::~Ignition() {}

void Ignition::start(int w, int h, DEngine::InputManager& im) {

	/*******************************************
	  *inicializacija glfw okna in nastavljanje
	  *opcij za reèeno okno (hints)
	  *******************************************/

	DEngine::setHeight(h);
	DEngine::setWidth(w);

	if (!glfwInit()) {
		printf_s("Could not initialise glfw\n");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(DEngine::width, DEngine::height, "DExplorer", nullptr, nullptr);

	if (m_window == nullptr) {
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf_s("Failed to initialize GLAD\n");
		return;
	}

	glfwSetWindowUserPointer(m_window, &im);
	glViewport(0, 0, DEngine::width, DEngine::height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}
