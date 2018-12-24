#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "MainGame.h"
#include <glm/glm.hpp>
#include <iostream>

int main() {
	MainGame game = MainGame();
	game.start();
	glfwTerminate();
}