#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include "MainGame.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main() {
	//sizeof(m_binders[binderName].vertices[0]) * m_binders[binderName].vertices.capacity()

	MainGame game = MainGame();
	game.start();
	glfwTerminate();
}