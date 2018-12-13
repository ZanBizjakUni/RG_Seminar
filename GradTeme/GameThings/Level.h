#pragma once
#include "kocka.h"
#include "Generator.h"
#include "Player.h"
#include <fstream>
#include <string>




class Level
{
public:
	Level(std::vector<kocka>& fc, std::vector<kocka>& ns, std::vector<kocka>& ew, std::vector<kocka>&, std::vector<kocka>&);
	Level();
	~Level();
	glm::vec3 getSP() { return m_startPoint; }
	glm::vec3 getEP() { return m_endPoint; }
	bool isInRoom(glm::vec3 playerPos);
	Room returnCurrRoom() { return m_currRoom; }
private:
	void generate();
	void createNorthWall(int, int);
	void createSouthWall(int, int);
	void createEastWall(int, int);
	void createWestWall(int, int);
	void createNorthDoor(int, int);
	void createSouthDoor(int, int);
	void createEastDoor(int, int);
	void createWestDoor(int, int);

	void makeFloor(int, int);
	void findSEPoint();
	
	std::vector<kocka>* m_FC;
	std::vector<kocka>* m_NS;
	std::vector<kocka>* m_EW;
	std::vector<std::string> m_lvlConstr;
	std::unordered_map<int, Room> m_rooms;
	std::unordered_map<int, Room> m_visitedRoooms;
	Room m_currRoom;
	Generator gen;
	glm::vec3 m_startPoint;
	glm::vec3 m_endPoint;
	float m_length = 2.0f;
	std::vector<kocka>* m_DPosEW;
	std::vector<kocka>* m_DPosNS;
	};

