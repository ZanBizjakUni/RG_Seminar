#include "Player.h"



Player::Player(): Camera() {
	m_speed = 2.5f;
	m_sprint = false;
	m_move = 0;
	m_pitch = 0.0f;
	m_yaw = 270.0f;
	m_stepHeight = 50; //higher value --> smaller height
	m_stepLen = 0.2f; //higher value --> longer step;
	m_prevPos = m_pos;
	m_downVelocity = 0.0f;
	m_colState = -1;
	m_prevColState = m_colState;
	m_status = Status::INAIR;
	m_bottomSphere = m_pos - glm::vec3(0.0f, 0.3f, 0.0f);
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
	m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));

	m_minAABB = glm::vec3(m_pos.x - 0.1f, m_pos.y - 0.75f, m_pos.z - 0.1f);
	m_maxAABB = glm::vec3(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f);

	m_state = PState::PLAY;
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

	m_corners[0] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners[1] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
	m_corners[2] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners[3] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
	m_corners[4] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners[5] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
	m_corners[6] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
	m_corners[7] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));

	m_minAABB = glm::vec3(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f);
	m_maxAABB = glm::vec3(m_pos.x + 0.1f, m_pos.y + 0.5f, m_pos.z + 0.1f);

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

	if ((m_colState == -1 && m_prevColState == 2) || (m_colState == 2 && m_prevColState == -1)) {
		m_status = Status::ONGROUND;
	}
	else if ((m_colState == 3 || m_colState == 1) && m_prevColState == -1) {
		m_status = Status::ONWALL;
	}
	else if (m_colState == -1 && m_prevColState == -1) {
		m_status = Status::INAIR;
	}

	if (m_prevColState == -1 && ( m_colState == 1 || m_colState == 3)) {
		m_downVelocity = 0;
	}
	//printf_s("%f %f %f\r", m_pos.x, m_pos.y, m_pos.z);


	Camera::update();
	
	
}

void Player::setBack(int d) {
	if (m_state == PState::PLAY) {
		switch (d) {
		case 1:
			m_pos = glm::vec3(m_prevPos.x, m_pos.y, m_pos.z);
			break;
		case 2:
			m_pos = glm::vec3(m_pos.x, m_prevPos.y, m_pos.z);
			break;
		case 3:
			m_pos = glm::vec3(m_pos.x, m_pos.y, m_prevPos.z);
			break;
		}
		m_bottomSphere = m_pos - glm::vec3(0.0f, 0.3f, 0.0f);
	}
	//m_pos = m_prevPos;
}

void Player::setColState(int c) {
	m_colState = c;
}

void Player::setPrevColState() {
	m_prevColState = m_colState;
}

void Player::setPrevPos() {
	m_prevPos = m_pos;
}

void Player::moveUp(float d) {
	if (m_state == PState::PLAY) {
		m_pos.y = m_prevPos.y;
		m_downVelocity = 0;
		m_bottomSphere.y = m_pos.y - 0.3f;
		m_corners[0] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners[1] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners[2] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners[3] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners[4] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners[5] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners[6] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
		m_corners[7] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));

		m_minAABB = glm::vec3(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f);
		m_maxAABB = glm::vec3(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f);
	}
}

void Player::jump() {
	if (m_state == PState::PLAY) {
		if (m_status == Status::ONGROUND || m_status == Status::ONWALL) {
			m_downVelocity -= 3.0f * DEngine::deltaTime;
		}
	}
}

void Player::gravity() {
	if (m_state == PState::PLAY) {
		if (m_colState == -1 || m_colState == 2) {
			m_downVelocity += DEngine::gravity * DEngine::deltaTime;
		}
		

		m_pos.y -= m_downVelocity;
		m_bottomSphere.y -= m_downVelocity;
		m_corners[0] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners[1] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners[2] = (glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners[3] = (glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners[4] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners[5] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners[6] = (glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
		m_corners[7] = (glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));

		m_minAABB = glm::vec3(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f);
		m_maxAABB = glm::vec3(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f);
	}
}

void Player::setState(PState s) {
	m_state = s;
}


