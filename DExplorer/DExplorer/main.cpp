#include "MainGame.h"
#include <GLFW/glfw3.h>

int main() {
	MainGame game = MainGame();
	game.start();
	glfwTerminate();
}