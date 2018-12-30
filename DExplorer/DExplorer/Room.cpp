#include "Room.h"


Room::Room() {}

Room::Room(glm::vec3 pos, Player* plyr) {
	m_pos = pos;
	m_plyr = plyr;
	m_selID = 0;
	m_stype = SelType::WALLS;
}


Room::~Room() {
}

void Room::addWall(Orientation ort) {
	if (m_walls.empty()) {
		m_walls.emplace_back(Wall("square", glm::vec4((m_pos), 1.0f)));
	}
	else {
		glm::vec3 prevPos = m_walls.back().getPos();
		m_walls.emplace_back(Wall("square", glm::vec4((prevPos), 1.0f)));

	}
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
	if (m_stype == SelType::LIGHTS) {
		for (auto& it : m_light) {
			it.unselect();
		}
	}
	else if (m_stype == SelType::WALLS) {
		m_walls[m_selID].unselect();
	}

	m_stype = SelType::WALLS;
	m_selID = m_walls.size() - 1;
	m_walls[m_selID].select();

}

void Room::addLight() {
	if (m_light.empty()) {
		m_light.emplace_back(Entity("cube", glm::vec4(m_pos,1)));

	}
	else {
		glm::vec3 prevPos = m_light.back().getPos();
		m_light.emplace_back(Entity("cube", glm::vec4(prevPos, 1.0f)));
	}
	m_light.back().scale(glm::vec3(0.2f, 0.2f, 0.2f));
	m_lightPos.emplace_back(m_light.back().getPos());
	m_lightCol.emplace_back(m_light.back().getColor());
	if (m_stype == SelType::WALLS) {
		m_walls[m_selID].unselect();
		m_selID = m_light.size() - 1;
	}
	else if (m_stype == SelType::LIGHTS) {
		m_light[m_selID].unselect();
	}
	m_stype = SelType::LIGHTS;
	m_selID = m_light.size() - 1;
	m_light[m_selID].select();
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
		shdr->set3f("lightColor", it.getColor());
		shdr->set1i("selected", it.isSeleced());

		it.draw(binder);
	}
}

void Room::selectFirstWall() {
	for (auto &it : m_walls) {
		it.unselect();

	}
	for (auto &it : m_light) {
		it.unselect();
	}
	if (!m_walls.empty()) {
		m_walls[0].select();
		m_selID = 0;
		m_stype = SelType::WALLS;
	}
}

void Room::selectFirstLight() {
	for (auto &it : m_walls) {
		it.unselect();

	}
	for (auto &it : m_light) {
		it.unselect();
	}
	if (!m_light.empty()) {
		m_light[0].select();
		m_selID = 0;
		m_stype = SelType::LIGHTS;
	}
}

void Room::moveSelected(Move mv) {
	switch (mv) {
	case Move::UP:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
			}
			else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
		}
		break;	
	case Move::DOWN:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
			}
			else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));

		}
		break;	
	case Move::LEFT:
		if (m_stype == SelType::WALLS) {
			m_walls[m_selID].translate(glm::vec3(-0.5f, 0.0f, 0.0f));
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(-0.5f, 0.0f, 0.0f));
		}
		break;
	case Move::RIGHT:
		if (m_stype == SelType::WALLS) {
			m_walls[m_selID].translate(glm::vec3(0.5f, 0.0f, 0.0f));
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(0.5f, 0.0f, 0.0f));

		}
		break;
	case Move::FORWARD:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
			}
			else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
		}
		break;
	case Move::BACKWARD:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
			}
			else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
		}
		break;	
	}
	if (m_stype == SelType::LIGHTS) {
		m_lightPos[m_selID] = m_light[m_selID].getPos();
	}

}

void Room::selectNext() {
	if (m_stype == SelType::WALLS) {
		m_walls[m_selID].unselect();
		m_selID++;
		m_selID = m_selID % m_walls.size();
		m_walls[m_selID].select();
	}
	else if (m_stype == SelType::LIGHTS) {
		m_light[m_selID].unselect();
		m_selID++;
		m_selID = m_selID % m_light.size();
		m_light[m_selID].select();
	}
	
}

void Room::selectPrev() {
	if (m_stype == SelType::WALLS) {
		m_walls[m_selID].unselect();
		m_selID--;
		m_selID = (m_selID+ m_walls.size()) % m_walls.size();
		m_walls[m_selID].select();
	}
	else if (m_stype == SelType::LIGHTS) {
		m_light[m_selID].unselect();
		m_selID--;
		m_selID = m_selID % m_light.size();
		m_light[m_selID].select();
	}
}


void Room::rotateSelected() {
	if (m_walls[m_selID].getOrientation() == Orientation::FLOOR) {
		m_walls[m_selID].rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (m_walls[m_selID].getOrientation() == Orientation::WALL) {
		m_walls[m_selID].rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}

void Room::delSelected() {
	if (m_stype == SelType::WALLS) {
		if (!m_walls.empty()) {
			m_walls[m_selID] = m_walls.back();
			m_walls.pop_back();
			if (!m_walls.empty()) {
				m_selID--;
				m_walls[m_selID].select();
			}
		}
	}
	if (m_stype == SelType::LIGHTS) {
		if (!m_light.empty()) {
			m_light[m_selID] = m_light.back();
			m_light.pop_back();
			if (!m_light.empty()) {
				m_selID--;
				m_light[m_selID].select();
			}

		}
	}
}

void Room::writeToFile(std::ofstream & file) {
	int tmp = 0;
	bool tmpB;
	tmp = m_walls.size();
	file.write((char*)&tmp, sizeof(tmp));
	for (auto &it : m_walls) {
		tmp = (int)it.getOrientation();
		file.write((char*)&tmp, sizeof(tmp));
		tmp = it.getTex().size();
		file.write((char*)&tmp, sizeof(tmp));
		for (auto &it1 : it.getTex()) {
			tmp = it1.size();
			file.write((char*)&tmp, sizeof(tmp));
			file.write((char*)it1.c_str(), tmp);
		}
		tmp = it.getRadius();
		file.write((char*)&tmp, sizeof(tmp));
		tmp = it.getBind().size();
		file.write((char*)&tmp, sizeof(tmp));
		file.write((char*)it.getBind().c_str(), it.getBind().size());
		file.write((char*)glm::value_ptr(it.getPos()), 3*sizeof(float));
		file.write((char*)glm::value_ptr(it.returnTransMat()), 16 * sizeof(float));
		file.write((char*)glm::value_ptr(it.getNormModel()), 9 * sizeof(float));
		tmpB = it.isTextureless();
		file.write((char*)&tmpB, sizeof(bool));
		tmpB = it.isSeleced();
		file.write((char*)&tmpB, sizeof(bool));
		file.write((char*)glm::value_ptr(it.getColor()), 3 * sizeof(float));
	}
}
