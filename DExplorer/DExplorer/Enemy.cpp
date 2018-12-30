#include "Enemy.h"



Enemy::Enemy() {}


Enemy::~Enemy() {}

void Enemy::update() {
	m_texCoord.y = 4;
	m_texCoord.x = (int)(glfwGetTime()*5) % 10;
}
