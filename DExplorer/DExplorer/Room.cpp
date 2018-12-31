#include "Room.h"


Room::Room() {}

Room::Room(glm::vec3 pos, Player* plyr) {
	m_pos = pos;
	m_plyr = plyr;
	m_selID = 0;
	m_stype = SelType::WALLS;
	for (int i = 0; i < 32; i++) {
		m_light.lightCol.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
		m_light.lightPos.emplace_back(m_pos);

	}
}


Room::~Room() {
}

void Room::addWall(WallType ort) {
	if (m_walls.empty()) {
		m_walls.emplace_back(Wall("square", glm::vec4((m_pos), 1.0f)));
	}
	else {
		glm::vec3 prevPos = m_walls.back().getPos();
		m_walls.emplace_back(Wall("square", glm::vec4((prevPos), 1.0f)));

	}
	switch (ort) {
	case WallType::FLOOR:
		m_walls.back().setTexBind("textures/stonebricks1.jpg");
		m_walls.back().rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		m_walls.back().setType(ort);
		break;
	case WallType::WALL:
		m_walls.back().setTexBind("textures/wall.jpg");
		m_walls.back().setType(ort);
		break;
	}
	if (m_stype == SelType::LIGHTS) {
		for (auto& it : m_light.lights) {
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
	if (m_light.lightSize < 32) {
		if (m_light.lights.empty()) {
			m_light.lights.emplace_back(Entity("cube", glm::vec4(m_pos, 1)));

		}
		else {
			glm::vec3 prevPos = m_light.lights.back().getPos();
			m_light.lights.emplace_back(Entity("cube", glm::vec4(prevPos, 1.0f)));
		}
		m_light.lights.back().scale(glm::vec3(0.2f, 0.2f, 0.2f));
		m_light.lights.back().setColor(glm::vec3(1.0f, 1.0f, 1.0f));
		m_light.lightPos[m_light.lightSize] = m_light.lights.back().getPos();
		m_light.lightCol[m_light.lightSize] = m_light.lights.back().getColor();


		if (m_stype == SelType::WALLS) {
			if (!m_walls.empty())
				m_walls[m_selID].unselect();
			m_selID = m_light.lights.size() - 1;
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].unselect();
		}
		m_stype = SelType::LIGHTS;
		m_selID = m_light.lights.size() - 1;
		m_light.lights[m_selID].select();
		m_light.lightSize++;
	}
}

void Room::addDoor() {
	if (m_stype == SelType::WALLS && !m_walls.empty()) {
		m_doors.emplace_back(Door("square", glm::vec4(m_walls[m_selID].getPos(), 1.0f)));
		
	}
	else if (m_stype == SelType::LIGHTS && !m_light.lights.empty()) {
		m_doors.emplace_back(Door("square", glm::vec4(m_light.lights[m_selID].getPos(), 1.0f)));
	}
	else if (m_stype == SelType::DOORS && !m_doors.empty()) {
		m_doors.emplace_back(Door("square", glm::vec4(m_doors[m_selID].getPos(), 1.0f)));
	}
	else {
		m_doors.emplace_back(Door("square", glm::vec4(m_pos, 1.0f)));
	}
	m_doors.back().setTexBind("textures/door.png");
	for (auto& it : m_walls) {
		it.unselect();
	}
	for (auto& it : m_light.lights) {
		it.unselect();
	}
	for (auto& it : m_doors) {
		it.unselect();
	}
	m_stype = SelType::DOORS;
	m_selID = m_doors.size() - 1;
	m_doors.back().select();
}



void Room::drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr) {
	shdr->use();
	for (auto& it : m_walls) {
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->setMat3fv("normModel", it.getNormModel());
		shdr->set3fv("lightColor", m_light.lightCol);
		shdr->set3f("viewPos", m_plyr->getPos());
		shdr->set3fv("lightPos", m_light.lightPos);
		shdr->set1i("selected", it.isSeleced());

		it.draw(binder);
	}

	
}

void Room::drawLights(DEngine::Binder binder, DEngine::ShadersComp * shdr) {
		shdr->use();
	for (auto& it : m_light.lights) {
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->set3f("lightColor", it.getColor());
		shdr->set1i("selected", it.isSeleced());

		it.draw(binder);
	}
}

void Room::drawDoors(DEngine::Binder binder, DEngine::ShadersComp * shdr) {
	shdr->use();
	for (auto& it : m_doors) {
		shdr->setMat4fv("model", it.returnTransMat());
		shdr->setMat4fv("view", m_plyr->returnView());
		shdr->setMat4fv("projection", m_plyr->returnProjection());
		shdr->setMat3fv("normModel", it.getNormModel());
		shdr->set3fv("lightColor", m_light.lightCol);
		shdr->set3f("viewPos", m_plyr->getPos());
		shdr->set3fv("lightPos", m_light.lightPos);
		shdr->set1i("selected", it.isSeleced());

		it.draw(binder);
	}
}

void Room::selectFirstWall() {
	for (auto &it : m_walls) {
		it.unselect();

	}
	for (auto &it : m_light.lights) {
		it.unselect();
	}
	for (auto&it : m_doors) {
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
	for (auto &it : m_light.lights) {
		it.unselect();
	}
	for (auto&it : m_doors) {
		it.unselect();
	}
	if (!m_light.lights.empty()) {
		m_light.lights[0].select();
		m_selID = 0;
		m_stype = SelType::LIGHTS;
	}
}

void Room::selectFirstDoor() {
	for (auto& it : m_walls) {
		it.unselect();
	}
	for (auto& it : m_light.lights) {
		it.unselect();
	}
	for (auto& it : m_doors) {
		it.unselect();
	}
	if (!m_doors.empty()) {
		m_doors[0].select();
		m_selID = 0;
		m_stype = SelType::DOORS;
	}
}



void Room::moveSelected(Move mv) {
	switch (mv) {
	case Move::UP:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getType() == WallType::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
			}
			else if (m_walls[m_selID].getType() == WallType::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
		}
		break;	
	case Move::DOWN:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getType() == WallType::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
			}
			else if (m_walls[m_selID].getType() == WallType::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));

		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
		}
		break;	
	case Move::LEFT:
		if (m_stype == SelType::WALLS) {
			m_walls[m_selID].translate(glm::vec3(-0.5f, 0.0f, 0.0f));
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(-0.5f, 0.0f, 0.0f));
		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(-0.5f, 0.0f, 0.0f));

		}
		break;
	case Move::RIGHT:
		if (m_stype == SelType::WALLS) {
			m_walls[m_selID].translate(glm::vec3(0.5f, 0.0f, 0.0f));
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(0.5f, 0.0f, 0.0f));

		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(0.5f, 0.0f, 0.0f));

		}
		break;
	case Move::FORWARD:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getType() == WallType::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.5f, 0.0f));
			}
			else if (m_walls[m_selID].getType() == WallType::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(0.0f, 0.0f, -0.5f));
		}
		break;
	case Move::BACKWARD:
		if (m_stype == SelType::WALLS) {
			if (m_walls[m_selID].getType() == WallType::FLOOR) {
				m_walls[m_selID].translate(glm::vec3(0.0f, -0.5f, 0.0f));
			}
			else if (m_walls[m_selID].getType() == WallType::WALL) {
				m_walls[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
			}
		}
		else if (m_stype == SelType::LIGHTS) {
			m_light.lights[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
		}
		else if (m_stype == SelType::DOORS) {
			m_doors[m_selID].translate(glm::vec3(0.0f, 0.0f, 0.5f));
		}
		break;	
	}
	if (m_stype == SelType::LIGHTS) {
		m_light.lightPos[m_selID] = m_light.lights[m_selID].getPos();
	}

	if (m_stype == SelType::WALLS) {
		m_walls[m_selID].setOrientation(m_walls[m_selID].getOrientation());
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
		m_light.lights[m_selID].unselect();
		m_selID++;
		m_selID = m_selID % m_light.lights.size();
		m_light.lights[m_selID].select();
	}
	else if (m_stype == SelType::DOORS) {
		m_doors[m_selID].unselect();
		m_selID++;
		m_selID = m_selID % m_doors.size();
		m_doors[m_selID].select();
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
		m_light.lights[m_selID].unselect();
		m_selID--;
		m_selID = m_selID % m_light.lights.size();
		m_light.lights[m_selID].select();
	}
	else if (m_stype == SelType::DOORS) {
		m_doors[m_selID].unselect();
		m_selID--;
		m_selID = m_selID % m_doors.size();
		m_doors[m_selID].select();
	}
}


void Room::rotateSelected() {
	if (m_stype == SelType::WALLS) {
		if (m_walls[m_selID].getType() == WallType::FLOOR) {
			m_walls[m_selID].rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			
		}
		else if (m_walls[m_selID].getType() == WallType::WALL) {
			m_walls[m_selID].rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		switch (m_walls[m_selID].getOrientation()) {
		case Orientation::NORTH:
			m_walls[m_selID].setOrientation(Orientation::WEST);
			break;
		case Orientation::SOUTH:
			m_walls[m_selID].setOrientation(Orientation::EAST);
			break;
		case Orientation::EAST:
			m_walls[m_selID].setOrientation(Orientation::NORTH);
			break;
		case Orientation::WEST:
			m_walls[m_selID].setOrientation(Orientation::SOUTH);
			break;
		case Orientation::UP:
			m_walls[m_selID].setOrientation(Orientation::DOWN);
			break;
		case Orientation::DOWN:
			m_walls[m_selID].setOrientation(Orientation::UP);

			break;

		}
	}
	else if (m_stype == SelType::DOORS) {
		m_doors[m_selID].rotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

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
	else if (m_stype == SelType::LIGHTS) {
		if (!m_light.lights.empty()) {
			m_light.lights[m_selID] = m_light.lights.back();
			m_light.lights.pop_back();
			m_light.lightCol[m_selID] = glm::vec3(0.0f, 0.0f, 0.0f);
			m_light.lightPos[m_selID] = m_pos;
			if (!m_light.lights.empty()) {
				m_selID--;
				m_light.lights[m_selID].select();
			}

		}
	}
	else if (m_stype == SelType::DOORS) {
		if (!m_doors.empty()) {
			m_doors[m_selID] = m_doors.back();
			m_doors.pop_back();
			if (!m_doors.empty()) {
				m_selID--;
				m_doors[m_selID].select();
			}
		}
	}
}

void Room::wallColider() {
	for (auto&it : m_walls) {
		m_plyr->setBack(m_collisionManager.checkCollision(m_plyr->getMinAABB(), m_plyr->getMaxAABB(), it.getMinAABB(), it.getMaxAABB()));
	}

}

void Room::writeToFile(std::ofstream & file) {
	int tmp = 0;
	bool tmpB;
	tmp = m_walls.size();
	file.write((char*)&tmp, sizeof(tmp));
	for (auto &it : m_walls) {
		tmp = (int)it.getType();
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
