#include "Ignition.h"


namespace DEngine {

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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

} // namespace
