#include "Player.h"

#include "GlobalVariables.h";
#include <GLFW\glfw3.h>

Player::Player(){
	;
}


Player::~Player()
{
}

void Player::init(glm::vec3 pos){
	printf("playerPos: %g %g %g\n", pos.x, pos.y, pos.z);
	m_position = pos;
	m_prevPos = pos;
	m_ori = true;
	m_camera.init(m_position);
}

void Player::update(PlayingGround::InputManager inputManager, GLuint pID, Collision* col) {
	m_secPrevPos = m_position;

	if (inputManager.isKeyDown(GLFW_KEY_W)) {
		m_position += (GameThings::cameraSpeed * GameThings::deltaTime) * glm::vec3(GameThings::cameraFront.x,0.0f, GameThings::cameraFront.z);
	}
	if (inputManager.isKeyDown(GLFW_KEY_S)) {
		m_position -= (GameThings::cameraSpeed * GameThings::deltaTime) * glm::vec3(GameThings::cameraFront.x, 0.0f, GameThings::cameraFront.z);
	}
	if (inputManager.isKeyDown(GLFW_KEY_A)) {
		m_position -= glm::normalize(glm::cross(GameThings::cameraFront, GameThings::cameraUp)) *(GameThings::cameraSpeed * GameThings::deltaTime);
	}
	if (inputManager.isKeyDown(GLFW_KEY_D)) {
		m_position += glm::normalize(glm::cross(GameThings::cameraFront, GameThings::cameraUp)) * (GameThings::cameraSpeed * GameThings::deltaTime);
	}
	if (inputManager.isKeyDown(GLFW_KEY_O)) {
		m_position.y += 0.2f;;
	}
	if (inputManager.isKeyDown(GLFW_KEY_P)) {
		m_position.y -= 0.2f;;
	}
	if (col->collisionCheck(m_position, m_ori)) {
		if (m_ori) {
			m_position.z = m_prevPos.z;
		}
		else {
			m_position.x = m_prevPos.x;
		}
	}

	GameThings::counter++;
	m_camera.update(pID, m_position);
	m_prevPos = m_position;
}
