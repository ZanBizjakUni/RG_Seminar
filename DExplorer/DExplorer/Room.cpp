#include "Room.h"

Room::Room() {}

Room::Room(glm::vec3 pos, Player* plyr) {
	m_pos = pos;
	m_plyr = plyr;
	m_selID = 0;
}


Room::~Room() {}

void Room::addWall(Orientation ort) {
	m_walls.emplace_back(Wall("square", glm::vec4((m_pos-1.0f),1.0f))); 
	switch (ort) {
	case Orientation::FLOOR:
		m_walls.back().setTexBind("textures/stonebricks1.jpg");
		m_walls.back().rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		m_walls.back().setOrientation(ort);
		break;
	case Orientation::WALL:
		m_walls.back().setTexBind("textures/wall.jpg");
		m_walls.back().setOrientation(ort);
		break;
	}
}

void Room::addLight() {
	m_light.emplace_back(Entity("cube", glm::vec4(m_pos,1)));
	m_light.back().scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_lightPos.emplace_back(m_light.back().getPos());
}

void Room::drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr) {
	shdr->use();
	for (auto& it : m_walls) {
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->setMat3fv("normModel", it.getNormModel());
		shdr->set3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shdr->set3f("viewPos", m_plyr->getPos());
		shdr->set3fv("lightPos", m_lightPos);
		shdr->set1i("selected", it.isSeleced());

		it.draw(binder);
	}

	
}

void Room::drawLights(DEngine::Binder binder, DEngine::ShadersComp * shdr) {
	for (auto& it : m_light) {
		shdr->use();
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->set3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

		it.draw(binder);
	}
}

void Room::selectFirstWall() {
	for (auto &it : m_walls) {
		it.unselect();

	}
	if (!m_walls.empty()) {
		m_walls[0].select();
		selectedWall = &m_walls[0];
		m_selID = 0;
	}
}

void Room::moveSelected(Move mv) {
	switch (mv) {
	case Move::UP:
		if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
		}
		else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
		}
		break;	
	case Move::DOWN:
		if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
		}
		else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
			m_walls[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
		}
		break;	
	case Move::LEFT:
		m_walls[m_selID].translate(glm::vec3(-1.0f, 0.0f, 0.0f));
		break;	
	case Move::RIGHT:
		m_walls[m_selID].translate(glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case Move::FORWARD:
		if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
		}
		break;
	case Move::BACKWARD:
		if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
			m_walls[m_selID].translate(glm::vec3(0.0f, -1.0f, 0.0f));
		}
		else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
			m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
		}
		break;
	
	
	}

}

void Room::selectNext() {
	m_walls[m_selID].unselect();
	m_selID++;
	m_selID = m_selID % m_walls.size();
	m_walls[m_selID].select();
}

void Room::selectPrev() {
	m_walls[m_selID].unselect();
	m_selID--;
	m_selID = ((m_selID % m_walls.size()) + m_walls.size()) % m_walls.size();
	m_walls[m_selID].select();
}


void Room::rotateSelected() {
	if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
		m_walls[m_selID].rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
		m_walls[m_selID].rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
