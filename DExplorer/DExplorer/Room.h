#pragma once

#include <Binder.h>
#include <ShadersComp.h>

#include "TexturedEntity.h"
#include "Player.h"

enum class Orientation {NORTH, SOUTH, WEST, EAST, FLOOR};

class Room {
public:
	Room();
	Room(glm::vec3 pos, Player plyr);
	~Room();

	void addWall(Orientation ort, glm::vec3 pos);
	void addLight();
	void drawWalls(DEngine::Binder binder, DEngine::ShadersComp* shdr, glm::mat4 view, glm::mat4 proj, glm::vec3 playerPos);
private:
	std::vector<TexturedEntity> m_walls;
	std::vector<Entity> m_light;
	Player* m_plyr;
	glm::mat4 m_model;
	glm::vec3 m_pos;

};