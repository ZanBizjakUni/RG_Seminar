#include "Enemy.h"


enum class State { IDLE = 0, MOVING = 2, ATTACK = 1, DEAD };

Enemy::Enemy() {}


Enemy::~Enemy() {}

void Enemy::update(glm::vec3 playerPos) {
	glm::vec3 deltaPos = playerPos - m_pos;
	if (m_health <= 0) {
		m_status = (int)State::DEAD;
	}
	else if (deltaPos.x <= 0.01f) {
		if (deltaPos.y <= 0.01f ) {
			if (deltaPos.z <= 0.01f) {
				m_status = (int)State::ATTACK;
			}
		}
	}
	else
	{
		m_status = (int)State::MOVING;
	}
	m_texCoord.y = m_status;
	m_texCoord.x = (int)(glfwGetTime() * 5) % 10;
	if (m_status == 2) {
		move(deltaPos);
	}
	
}

void Enemy::move(glm::vec3 deltaPos) {
	m_dir = glm::normalize(deltaPos);
	if (deltaPos.x < 0.0f && deltaPos.y < 0.0f && deltaPos.z < 0.0f) {
		m_pos -= m_dir * m_speed;
	}
	else
	{
		m_pos += m_dir * m_speed;
	}
	
	//Entity::translate(m_pos);
}
