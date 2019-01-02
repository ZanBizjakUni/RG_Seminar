#include "Wall.h"



Wall::Wall() {}

Wall::Wall(std::ifstream & file): TexturedEntity(file) {
	int tmp;
	file.read((char*)&tmp, sizeof(int));
	m_orientation = (Orientation)tmp;
	file.read((char*)&tmp, sizeof(int));
	m_type = (WallType)tmp;
}

Wall::Wall(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {
	
}


Wall::~Wall() {}

void Wall::setType(WallType o) {
	m_type = o;
	if (o == WallType::FLOOR) {
		setOrientation(Orientation::UP);
	}
	else if (o == WallType::WALL) {
		setOrientation(Orientation::SOUTH);
	}
}

void Wall::setOrientation(Orientation o) {
	m_orientation = o;
	switch (m_orientation) {
	case Orientation::NORTH:
		m_minAABB = glm::vec4(m_pos.x - m_radius, m_pos.y - m_radius, m_pos.z - 0.1f, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + m_radius, m_pos.y + m_radius, m_pos.z + 0.1f, 1.0f);
		break;
	case Orientation::SOUTH:
		m_minAABB = glm::vec4(m_pos.x - m_radius, m_pos.y - m_radius, m_pos.z - 0.1f, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + m_radius, m_pos.y + m_radius, m_pos.z + 0.1f, 1.0f);
		break;
	case Orientation::EAST:
		m_minAABB = glm::vec4(m_pos.x - 0.1f, m_pos.y - m_radius, m_pos.z - m_radius, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + 0.1f, m_pos.y + m_radius, m_pos.z + m_radius, 1.0f);

		break;
	case Orientation::WEST:
		m_minAABB = glm::vec4(m_pos.x - 0.1f, m_pos.y - m_radius, m_pos.z - m_radius, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + 0.1f, m_pos.y + m_radius, m_pos.z + m_radius, 1.0f);
		break;
	case Orientation::UP:
		m_minAABB = glm::vec4(m_pos.x - m_radius, m_pos.y - 0.1f, m_pos.z - m_radius, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + m_radius, m_pos.y + 0.1f, m_pos.z + m_radius, 1.0f);
		break;
	case Orientation::DOWN:
		m_minAABB = glm::vec4(m_pos.x - m_radius, m_pos.y - 0.1f, m_pos.z - m_radius, 1.0f);
		m_maxAABB = glm::vec4(m_pos.x + m_radius, m_pos.y + 0.1f, m_pos.z + m_radius, 1.0f);
		break;

	}
}

void Wall::writeToFile(std::ofstream& file) {
	TexturedEntity::writeToFile(file);
	int tmp = (int)m_orientation;
	file.write((char*)&tmp, sizeof(int));
	tmp = (int)m_type;
	file.write((char*)&tmp, sizeof(int));
}
