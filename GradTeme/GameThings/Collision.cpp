#include "Collision.h"



void Collision::init(std::vector<kocka>EW, std::vector<kocka>NS){
	for (auto it : EW) {
		m_walls.emplace_back(it);
	}
	for (auto it : NS) {
		m_walls.emplace_back(it);
	}
}

bool Collision::collisionCheck(glm::vec3 playerPos, bool& ori){
	std::vector<kocka> tmpWalls = proximityCheck(playerPos);
//	printf("num of walls: %d \n", tmpWalls.size());
	if (!tmpWalls.empty()) {
		for (auto it : tmpWalls) {
			switch (it.returnSide()) {
			case Side::NORTH:
	//			printf("NORTH\n");
				if ((playerPos.z - 0.12f) < it.returnPosition().z) {
					ori = true;
					return true;
				}
				break;
			case Side::SOUTH:
	//			printf("SOUTH\n");
				if ((playerPos.z + 0.12f) > it.returnPosition().z) {
					ori = true;
					return true;
				}
				break;
			case Side::EAST:
	//			printf("EAST\n");
				if ((playerPos.x + 0.12f) > it.returnPosition().x) {
					ori = false;
					return true;
				}
				break;
			case Side::WEST:
	//			printf("WEST\n");
				if ((playerPos.x - 0.12f) < it.returnPosition().x) {
					ori = false;
					return true;
				}
				break;
			}
		}
	}
	return false;
}

std::vector<kocka> Collision::proximityCheck(glm::vec3 playerPos){
	std::vector<kocka> proximityWalls;
	for (auto it : m_walls) {
		if (glm::distance(glm::vec2(it.returnPosition().x, it.returnPosition().z), glm::vec2(playerPos.x, playerPos.z)) < m_radius) {
			proximityWalls.emplace_back(it);
		}
	}
	return proximityWalls;
}

Collision::Collision(){
}


Collision::~Collision(){
}
