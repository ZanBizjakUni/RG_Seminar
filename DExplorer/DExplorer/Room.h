#pragma once

#include <fstream>

#include <Binder.h>
#include <ShadersComp.h>

#include "Wall.h"
#include "Player.h"


enum class Move {UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};

enum class SelType { WALLS, LIGHTS };

class Room {
public:
	Room();
	Room(glm::vec3 pos, Player* plyr);
	~Room();

	void addWall(Orientation ort);
	void addLight();
	void drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void drawLights(DEngine::Binder binder, DEngine::ShadersComp* shdr);
	void selectFirstWall();
	void selectFirstLight();
	void moveSelected(Move mv);
	void selectNext();
	void selectPrev();
	void rotateSelected();
	void delSelected();
	void writeToFile(std::ofstream& file);
private:
	std::vector<Wall> m_walls;
	std::vector<Entity> m_light;
	std::vector<glm::vec3> m_lightPos;
	std::vector<glm::vec3> m_lightCol;
	Player* m_plyr;
	glm::mat4 m_model;
	glm::vec3 m_pos;
	int m_selID;
	SelType m_stype;
};