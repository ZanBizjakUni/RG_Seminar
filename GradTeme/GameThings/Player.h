#pragma once

#include <PlayingGround\InputManager.h>
#include <PlayingGround\Camera.h>
#include "Collision.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();
	void init(glm::vec3);
	void update(PlayingGround::InputManager inputManager, GLuint pID, Collision* col);
	glm::vec3 returnLookAt() { return m_camera.returnLookAt(); }
	glm::vec3 getPos() { return m_position; }
	glm::vec3 returnPrevPos() { return m_secPrevPos; }
private:
	//m_positon je za pozicijo igralca in za kamero.
	glm::vec3 m_position;
	glm::vec3 m_prevPos;
	glm::vec3 m_secPrevPos;
	bool m_ori;
	unsigned int counter = 0;
	PlayingGround::Camera m_camera;
};

