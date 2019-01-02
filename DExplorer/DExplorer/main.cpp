#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "MainGame.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main() {
	printf_s("%d\n", sizeof(int));
	MainGame game = MainGame();

	game.start();
	glfwTerminate();
}