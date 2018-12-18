#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "MainGame.h"

int main() {

	MainGame game = MainGame();
	game.start();
	glfwTerminate();
}