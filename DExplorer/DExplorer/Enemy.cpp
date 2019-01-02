#include "Enemy.h"



Enemy::Enemy(){}
Enemy::Enemy(std::ifstream & file): TexturedEntity(file) {
	file.read((char*)glm::value_ptr(m_texCoord), 2 * sizeof(float));
	file.read((char*)glm::value_ptr(m_offset), 2 * sizeof(float));
	file.read((char*)glm::value_ptr(m_dir), 3 * sizeof(float));
	file.read((char*)&m_speed, sizeof(float));
	int tmp;
	file.read((char*)&tmp, sizeof(int));
	m_status = (State)tmp;
	file.read((char*)&m_health, sizeof(float));
}
Enemy::Enemy(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {
	m_status = State::IDLE;

}




Enemy::~Enemy() {}

void Enemy::update(glm::vec3 playerPos) {
	playerPos -= glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 deltaPos = playerPos - glm::vec3(m_pos.x, m_pos.y, m_pos.z);
	if (m_health <= 0) {
		m_status = State::DEAD;
	}
	else if (glm::distance(playerPos, glm::vec3(m_pos)) <= 0.5f) {
		m_status = State::ATTACK;
	}
	else if(glm::distance(playerPos, glm::vec3(m_pos)) <= 3.0f)
	{
		m_status = State::MOVING;
	}
	else if (glm::distance(playerPos, glm::vec3(m_pos)) >= 3.0f) {
		m_status = State::IDLE;
	}
	m_texCoord.y = (float)m_status;
	m_texCoord.x = (float)((int)(glfwGetTime() * 5) % 10);
	if (m_status == State::MOVING) {
		move(deltaPos);
	}
	
}

void Enemy::writeToFile(std::ofstream & file) {
	TexturedEntity::writeToFile(file);
	DEngine::FileManager::write2f(file, m_texCoord);
	DEngine::FileManager::write2f(file, m_offset);
	DEngine::FileManager::write3f(file, m_dir);
	file.write((char*)&m_speed, sizeof(float));
	int tmp;
	tmp = (int)m_status;
	file.write((char*)&tmp, sizeof(int));
	file.write((char*)&m_health, sizeof(float));
}

void Enemy::move(glm::vec3 deltaPos) {
	m_dir = glm::normalize(deltaPos);
	m_dir *= m_speed * DEngine::deltaTime;
	m_dir.y = 0.0f;
	/*if (deltaPos.x < 0.0f && deltaPos.y < 0.0f && deltaPos.z < 0.0f) {
		m_pos -= m_dir * m_speed;
	}
	else
	{
		m_pos += m_dir * m_speed;
	}*/
	
	Entity::translate(m_dir);
}
