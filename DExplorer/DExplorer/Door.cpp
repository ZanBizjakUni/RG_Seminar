#include "Door.h"



Door::Door() {}

Door::Door(std::ifstream & file): Wall(file) {
	file.read((char*)&m_isOpened, sizeof(bool));
}

Door::Door(std::string bindName, glm::vec4 p): Wall(bindName, p) {
	m_isOpened = false;
}


Door::~Door() {}

void Door::openClose() {
	if (!m_isOpened) {
		translate(glm::vec3(0.5f, 0.0f, -0.5f));
		rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		//m_minAABB -= glm::vec4(-0.5f, 0.0f, -0.5f, 0.0f);
	//	m_maxAABB -= glm::vec4(-0.5f, 0.0f, -0.5f, 0.0f);
		m_isOpened = true;
	}
	else {
		rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		translate(glm::vec3(-0.5f, 0.0f, 0.5f));
		m_isOpened = false;
	}
}

void Door::writeToFile(std::ofstream & file) {
	Wall::writeToFile(file);
	file.write((char*)&m_isOpened, sizeof(bool));
}
