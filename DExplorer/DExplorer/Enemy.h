#pragma once

#include "TexturedEntity.h"

class Enemy: public TexturedEntity{
public:
	Enemy();
	Enemy(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {}
	~Enemy();
	void update();

	glm::vec2 getTexCoord() { return m_texCoord; }
	glm::vec2 getOffset() { return m_offset; }
private:
	glm::vec2 m_texCoord;
	glm::vec2 m_offset = glm::vec2(0.1f, 0.2f);
};

