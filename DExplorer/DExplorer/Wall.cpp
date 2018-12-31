#include "Wall.h"



Wall::Wall() {}

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
