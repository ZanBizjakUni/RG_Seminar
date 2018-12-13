#include "Level.h"
#include "GlobalVariables.h"
#include <glm\glm.hpp>
Level::Level(std::vector<kocka>& fc, std::vector<kocka>& ns, std::vector<kocka>& ew, std::vector<kocka>& ewD, std::vector<kocka>& nsD) {
	m_NS = &ns;
	m_NS->clear();
		
	m_FC = &fc;
	m_FC->clear();

	m_EW = &ew;
	m_EW->clear();

	m_DPosEW = &ewD;
	m_DPosNS = &nsD;
	m_DPosEW->clear();
	m_DPosNS->clear();
	m_lvlConstr.clear();
	m_lvlConstr = gen.generate();
	m_rooms.clear();
	m_rooms = gen.getRooms();
	findSEPoint();
	generate();
}

Level::Level(){
}




Level::~Level()
{
}

bool Level::isInRoom(glm::vec3 playerPos){
	float x1, x2, x3, x4;
	float z1, z2, z3, z4;
	int id;
	for (auto it : m_rooms) {
		x1 = it.second.x * m_length;
		z1 = it.second.z * m_length;
		
		x2 = it.second.topRightX * m_length;
		z2 = it.second.topRightZ * m_length;

		x3 = it.second.bottomLeftX * m_length;
		z3 = it.second.bottomLeftZ * m_length;
		
		x4 = it.second.bottomRightX * m_length;
		z4 = it.second.bottomRightZ * m_length;

		if (playerPos.x > x1 && playerPos.z > z1) {
			if (playerPos.x < x2 && playerPos.z > z2) {
				if (playerPos.x > x3 && playerPos.z < z3) {
					if (playerPos.x < x4 && playerPos.z < z4) {
						m_currRoom = it.second;
						id = it.first;
						m_rooms.erase(id);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Level::generate()	{
	printf("\nm_lvlConstr[0].size: %d\n m_lvlConstr.size: %d \n",m_lvlConstr[0].size(), m_lvlConstr.size());
	for (size_t i = 0; i < m_lvlConstr.size(); i++) {
		for (size_t j = 0; j < m_lvlConstr[i].size(); j++) {		
			if (m_lvlConstr[i][j] == 'F' || m_lvlConstr[i][j] == 'S') {
				if (i != 0) {
					if (m_lvlConstr[i - 1][j] == '#') {
						createNorthWall(j, i);
					}
					else if (m_lvlConstr[i][j] == 'F') {
						if (m_lvlConstr[i - 1][j] == 'S') {
							createNorthWall(j, i);
						}
					}
				}
				else if (i == 0) {
					createNorthWall(j, i);
				}
					
				if (j != 0) {
					if (m_lvlConstr[i][j - 1] == '#') {
						createWestWall(j, i);
					}
					else if (m_lvlConstr[i][j] == 'F') {
						if (m_lvlConstr[i][j - 1] == 'S') {
							createWestWall(j, i);
						}
					}
				}
				else if (j == 0) {
					createWestWall(j, i);
				}
				if (i + 1 !=  m_lvlConstr.size()) {
					if (m_lvlConstr[i + 1][j] == '#') {
						createSouthWall(j, i);
					}
					else if (m_lvlConstr[i][j] == 'F') {
						if (m_lvlConstr[i + 1][j] == 'S') {
							createSouthWall(j, i);
						}
					}
				}
				else if (i == m_lvlConstr.size() - 1) {
					createSouthWall(j, i);
				}
				if (j + 1 < m_lvlConstr[i].size()) {
					if (m_lvlConstr[i][j + 1] == '#') {
						createEastWall(j, i);
					}
					else if (m_lvlConstr[i][j] == 'F') {
						if (m_lvlConstr[i][j + 1] == 'S') {
							createEastWall(j, i);
						}
					}
				}
				else if (j == m_lvlConstr[i].size() == 0) {
					createEastWall(j, i);
				}
				makeFloor(j, i);
			}
			else if (m_lvlConstr[i][j] == 'D') {
				if (m_lvlConstr[i - 1][j] == 'F') {
					createEastWall(j, i);
					createWestWall(j, i);
					createNorthDoor(j, i);
				}
				if(m_lvlConstr[i + 1][j] == 'F'){
					createEastWall (j,i);
					createWestWall (j, i);
					createSouthDoor(j, i);
				}
				if (m_lvlConstr[i][j - 1] == 'F') {
					createNorthWall(j, i);
					createSouthWall(j, i);
					createWestDoor(j, i);
				}
				if (m_lvlConstr[i][j + 1] == 'F') {
					createNorthWall(j, i);
					createSouthWall(j, i);
					createEastDoor(j, i);
				}
				makeFloor(j, i);
			}
				
		}
	}
}

void Level::createNorthWall(int xMulti, int zMulti)	{
	m_NS->emplace_back();
	m_NS->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_NS->back().indentify(Side::NORTH);
}

void Level::createSouthWall(int xMulti, int zMulti){
	m_NS->emplace_back();
	m_NS->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_NS->back().indentify(Side::SOUTH);
}

void Level::createEastWall(int xMulti, int zMulti){
	m_EW->emplace_back();
	m_EW->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_EW->back().indentify(Side::EAST);
}

void Level::createWestWall(int xMulti, int zMulti){
	m_EW->emplace_back();
	m_EW->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_EW->back().indentify(Side::WEST);
}

void Level::createNorthDoor(int xMulti, int zMulti){
	m_DPosNS->emplace_back();
	m_DPosNS->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_DPosNS->back().indentify(Side::NORTH);
}

void Level::createSouthDoor(int xMulti, int zMulti){
	m_DPosNS->emplace_back();
	m_DPosNS->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_DPosNS->back().indentify(Side::SOUTH);
}

void Level::createEastDoor(int xMulti, int zMulti){
	m_DPosEW->emplace_back();
	m_DPosEW->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_DPosEW->back().indentify(Side::EAST);
}

void Level::createWestDoor(int xMulti, int zMulti){
	m_DPosEW->emplace_back();
	m_DPosEW->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_DPosEW->back().indentify(Side::WEST);
}

void Level::makeFloor(int xMulti, int zMulti ){
	m_FC->emplace_back();
	m_FC->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_FC->back().indentify(Side::FLOOR);

	m_FC->emplace_back();
	m_FC->back().init(GameThings::chID, glm::vec3(m_length * (float)xMulti, 0.0f, m_length * (float)zMulti));
	m_FC->back().indentify(Side::CEIL);
}


//najde spawn in konèno toèko
void Level::findSEPoint() {
	int start;
	int end;
	do {
		start = rand() % (m_rooms.size() - 1);
	} while (m_rooms[start].x == 0 || m_rooms[start].z == 0);
	m_startPoint.x = m_rooms[start].x + (m_rooms[start].sizeX / 2);
	m_startPoint.z = m_rooms[start].z + (m_rooms[start].sizeY / 2);
	m_startPoint.x *= m_length;
	m_startPoint.y = 1.0f;
	m_startPoint.z *= m_length;
	
	int a;
	do {
		end = rand() % (m_rooms.size() - 1);
	} while (end == start || (m_rooms[end].x == 0 || m_rooms[end].z == 0));
	m_endPoint.x = m_rooms[end].x + (m_rooms[end].sizeX / 2);
	m_endPoint.z = m_rooms[end].z + (m_rooms[end].sizeY / 2);
	printf("rooms[end]X/Z: %d %d", m_rooms[end].x, m_rooms[end].z);
	m_rooms.erase(start);
	m_rooms.erase(end);
	m_lvlConstr[m_endPoint.z][m_endPoint.x] = 'E';
	m_endPoint.x *= m_length;
	m_endPoint.y = 0.0f;
	m_endPoint.z *= m_length;
	
}
