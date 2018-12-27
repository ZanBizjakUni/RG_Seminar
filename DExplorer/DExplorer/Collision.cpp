#include "Collision.h"
#include <iostream>
#include <string>
using namespace std;

Collision::Collision(Player* plyr) {
	m_plyr = plyr;
}

Collision::~Collision() {};

bool Collision::ifCollision(Entity m_entity) {
	cout << "ifCollision test" << endl;
	glm::vec3(m_plyrPos) = m_plyr->getPos();
	glm::vec3(m_entAABBMax) = m_entity.getBbox().AABoundBox::getMaxExtend();
	glm::vec3(m_entAABBMin) = m_entity.getBbox().AABoundBox::getMinExtend();
	if ((m_plyrPos.x >= m_entAABBMin.x && m_plyrPos.x <= m_entAABBMax.x) &&
		(m_plyrPos.y >= m_entAABBMin.y && m_plyrPos.y <= m_entAABBMax.y) &&
		(m_plyrPos.z >= m_entAABBMin.z && m_plyrPos.z <= m_entAABBMax.z)){
		cout << "true" << endl;
		return true;
	}
	cout << "m_plyrPos.x >= m_entAABBMin.x: "  << (m_plyrPos.x >= m_entAABBMin.x) << endl;
	cout << "m_plyrPos.x <= m_entAABBMax.x: "  << (m_plyrPos.x <= m_entAABBMax.x) << endl;
	cout << "m_plyrPos.y >= m_entAABBMin.y: "  << (m_plyrPos.y >= m_entAABBMin.y) << endl;
	cout << "m_plyrPos.y >= m_entAABBMax.y: "  << (m_plyrPos.y <= m_entAABBMax.y) << endl;
	cout << "m_plyrPos.z >= m_entAABBMin.z: "  << (m_plyrPos.z >= m_entAABBMin.z) << endl;
	cout << "m_plyrPos.z <= m_entAABBMax.z: "  << (m_plyrPos.z <= m_entAABBMax.z) << endl;
	return false;
}