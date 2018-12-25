#include "Room.h"



Room::Room() {}

Room::Room(glm::vec3 pos, Player plyr) {
	m_pos = pos;
	m_plyr = &plyr;
}


Room::~Room() {}

void Room::addWall(Orientation ort, glm::vec3 pos) {
	m_walls.emplace_back(TexturedEntity("square", glm::vec4(pos,1.0f))); 
	m_walls.back().setTexBind("textures/container.jpg");
	switch (ort) {
	case Orientation::FLOOR:
		m_walls.back().rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	}
}

void Room::drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr, glm::mat4 view, glm::mat4 proj, glm::vec3 playerPos) {
	for (auto& it : m_walls) {
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->setMat3fv("normModel", it.getNormModel());
		shdr->set3f("lightColor", m_light.getColor());
		shdr->set3f("viewPos", m_plyr->getPos());
		shdr->set3f("lightPos", m_light.getPos());
		shdr->set1i("arrSize", 1);
	}
}
