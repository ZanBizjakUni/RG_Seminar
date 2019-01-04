#include "Player.h"



Player::Player(): Camera(), Physics(m_pos) {
	m_speed = 2.5f;
	m_sprint = false;
	m_move = 0;
	m_pitch = 0.0f;
	m_yaw = 270.0f;
	m_stepHeight = 50; //higher value --> smaller height
	m_stepLen = 0.2f; //higher value --> longer step;
	m_prevPos = m_pos;
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));

	m_minAABB = glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.75f, m_pos.z - 0.1f, 1.0f);
	m_maxAABB = glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f);

	m_state = PState::CREATE;
}


Player::~Player() {}

void Player::move(Direction d) {
	//m_pos += glm::vec3(0.0f, sin(m_move/m_stepLen)/m_stepHeight, 0.0f);
	glm::vec3 t = glm::vec3(0.0f, 0.0f, 0.0f);
	m_move += 0.05;
	glm::vec3 change;
	if (d == Direction::FORWARD) {
		if (m_state == PState::CREATE) {
			change = ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, m_front.y, m_front.z);

		}
		else {
			change = ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, 0.0f, m_front.z);
		}
		m_pos += change;
		m_bottomSphere += change;
	
	}
	
	if (d == Direction::BACKWARD) {
		if (m_state == PState::CREATE) {
			change = ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, m_front.y, m_front.z);

		}
		else {
			
			change = ((m_speed * (float)DEngine::deltaTime) * ((int)m_sprint + 1))  * glm::vec3(m_front.x, 0.0f, m_front.z);
		}
		m_pos -= change;
		m_bottomSphere -= change;
	}

	if (d == Direction::LEFT) {
		change = glm::normalize(glm::cross(m_front, m_up)) * (m_speed * (float)DEngine::deltaTime);
		m_pos -= change;
		m_bottomSphere -= change;
	}
	if (d == Direction::RIGHT) {
		change = glm::normalize(glm::cross(m_front, m_up)) * (m_speed * (float)DEngine::deltaTime);
		m_pos += change;
		m_bottomSphere += change;

	}
	DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

}

void Player::toggleSprint() {
	m_sprint = true;
}

void Player::unToggleSprint() {
	m_sprint = false;
}

void Player::update(glm::vec2 offset) {
	offset.x *= DEngine::sensitivity;
	offset.y *= DEngine::sensitivity;
	m_yaw += offset.x;
	m_pitch += offset.y;
	if (m_pitch > 89.0f) {
		m_pitch = 89.0f;
	}
	if (m_pitch < -89.0f) {
		m_pitch = -89.0f;
	}
	m_front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	m_front.y = sin(glm::radians(m_pitch));
	m_front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	m_front = glm::normalize(m_front);

	Physics::update();
	printf_s("%d\n", m_status);
	//printf_s("%f %f %f\r", m_pos.x, m_pos.y, m_pos.z);


	Camera::update();
	
	
}

void Player::setBack(int d) {
	if (m_state == PState::PLAY) {
		Physics::setBack(m_pos, m_prevPos, d);
	}
	//m_pos = m_prevPos;
}
/*
void Player::setColState(int c) {
	m_colState = c;
}
*/


void Player::setPrevPos() {
	m_prevPos = m_pos;
}

void Player::moveUp(float d) {
	if (m_state == PState::PLAY) {
		Physics::moveUp(m_pos, m_prevPos, d);
		DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);

	}
}

void Player::jump() {
	if (m_state == PState::PLAY) {
		if (m_status == Status::ONGROUND || m_status == Status::ONWALL) {
			m_downVelocity -= 2.5f * DEngine::deltaTime;
		}
	}
}

void Player::gravity() {
	if (m_state == PState::PLAY) {
		Physics::gravity(m_pos);
		DEngine::CollisionManager::changeAABB(m_minAABB, m_maxAABB, m_pos);
	}
}

void Player::setState(PState s) {
	m_state = s;
}


