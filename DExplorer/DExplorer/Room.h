#pragma once

#include <fstream>

#include <Binder.h>
#include <ShadersComp.h>
#include <CollisionManager.h>

#include "Wall.h"
#include "Player.h"
#include "Door.h"
#include "Enemy.h"

enum class Move {UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};

enum class SelType { WALLS, LIGHTS, DOORS, ENEMY };

struct Light {
	std::vector<Entity> lights;
	int lightSize = 0;
	std::vector<glm::vec3> lightPos;
	std::vector<glm::vec3> lightCol;
};

class Room {
public:
	Room();
	Room(std::ifstream& file, Player* p);
	Room(glm::vec3 pos, Player* plyr);
	~Room();

	void addWall(WallType ort);
	void addLight();
	void addDoor();
	void addEnemy();
	void drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void drawLights(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void drawDoors(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void drawEnemies(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void selectFirstWall();
	void selectFirstLight();
	void selectFirstDoor();
	void selectFistEnemy();
	void moveSelected(Move mv);
	void selectNext();
	void selectPrev();
	void rotateSelected();
	void delSelected();
	void wallColider();
	void checkDoors();
	void checkEnemies(); 
	void checkBox();
	void unselectAll();
	glm::vec3 getMinPos() { return minPos; }
	glm::vec3 getMaxPos() { return maxPos; }
	glm::vec3 getLastDoorPos() { return m_doors.back().getPos(); }
	void writeToFile(std::ofstream& file);
private:
	std::vector<Wall> m_walls;
	Light m_light;
	std::vector<Door> m_doors;
	Player* m_plyr;
	glm::mat4 m_model;
	glm::vec3 m_pos;
	int m_selID;
	DEngine::CollisionManager m_collisionManager;
	SelType m_stype;
	std::vector<Enemy> m_enemies;
	glm::vec3 minPos;
	glm::vec3 maxPos;
};