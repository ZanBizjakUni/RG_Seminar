#include "Enemy.h"


enum class State { IDLE = 4, MOVING = 2, ATTACK = 1, DEAD = 0 };

Enemy::Enemy() {}


Enemy::~Enemy() {}

void Enemy::update(glm::vec3 playerPos) {
	glm::vec3 deltaPos = playerPos - m_pos;
	float distance = glm::distance(playerPos, m_pos);
	if (m_health <= 0) {
		m_status = (int)State::DEAD;
	}
	else if (distance < 0.5f) {
		m_status = (int)State::ATTACK;
	}
	else if (distance < 3.0f)
	{
		if (m_status == (int)State::MOVING && distance < 10.0f) {
			m_status = (int)State::MOVING;
		}
		else if (m_status == (int)State::IDLE) {
			m_status = (int)State::MOVING;
		}
		else if (m_status == (int)State::ATTACK && distance > 1.5f) {
			m_status = (int)State::MOVING;
		}
	}
	else {
		m_status = (int)State::IDLE;
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
		m_pos -= m_dir * (m_speed * (float)DEngine::deltaTime);
	}
	else
	{
		m_pos += m_dir * (m_speed * (float)DEngine::deltaTime);
	}
	
	//Entity::translate(m_pos);
}
