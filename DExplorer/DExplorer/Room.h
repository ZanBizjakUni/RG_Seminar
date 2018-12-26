#pragma once

#include <Binder.h>
#include <ShadersComp.h>

#include "Wall.h"
#include "Player.h"


enum class Move {UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD};


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
	void moveSelected(Move mv);
	void selectNext();
	void selectPrev();
	void rotateSelected();
private:
	std::vector<Wall> m_walls;
	std::vector<Entity> m_light;
	std::vector<glm::vec3> m_lightPos;
	Player* m_plyr;
	TexturedEntity* selectedWall;
	glm::mat4 m_model;
	glm::vec3 m_pos;
	int m_selID;

};