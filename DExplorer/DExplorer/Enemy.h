#pragma once

#include "TexturedEntity.h"

class Enemy: public TexturedEntity{
public:
	Enemy();
	Enemy(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {}
	~Enemy();
	void update(glm::vec3 playerPos);

	glm::vec2 getTexCoord() { return m_texCoord; }
	glm::vec2 getOffset() { return m_offset; }
	glm::vec3 getPos() { return m_pos; }
	int getStatus() { return m_status; }
private:
	void move(glm::vec3 playerPos);
	glm::vec2 m_texCoord;
	glm::vec2 m_offset = glm::vec2(0.1f, 0.2f);
	glm::vec3 m_pos = Entity::getPos();
	glm::vec3 m_dir;
	float m_speed = 0.5f;
	int m_status = 4; 
	float m_health = 1;
};

