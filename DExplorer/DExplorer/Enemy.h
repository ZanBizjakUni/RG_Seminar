#pragma once

#include "TexturedEntity.h"

enum class State { DEAD, ATTACK, MOVING, IDLE };


class Enemy: public TexturedEntity{
public:
	Enemy();
	Enemy(std::ifstream& file);
	Enemy(std::string bindName, glm::vec4 p);
	~Enemy();
	void update(glm::vec3 playerPos);

	glm::vec2 getTexCoord() { return m_texCoord; }
	glm::vec2 getOffset() { return m_offset; }
	glm::vec3 getPos() { return m_pos; }
	void writeToFile(std::ofstream& file);
	void die();
private:
	void move(glm::vec3 playerPos);
	glm::vec2 m_texCoord;
	glm::vec2 m_offset = glm::vec2(0.1f, 0.2f);
	glm::vec3 m_dir;
	float m_speed = 0.5f;
	State m_status; 
	float m_health = 1.0;
	float m_deathTime;
};

