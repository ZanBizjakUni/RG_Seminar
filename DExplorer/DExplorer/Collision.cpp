#include "Collision.h"

Collision::Collision(Player* plyr) {
	m_plyr = plyr;
	 
}

Collision::~Collision() {};

bool Collision::ifCollision(Entity m_entity) {
	glm::vec3(m_plyrPos) = m_plyr->getPos();
	glm::vec3(m_entPos) = m_entity.getPos();
	if ((m_plyrPos.x - m_entPos.x <= 1000) && (m_plyrPos.y - m_entPos.y) <= 1000 &&
		(m_plyrPos.z - m_entPos.z <= 1000)){
		
		return true;
	}
	return false;
}