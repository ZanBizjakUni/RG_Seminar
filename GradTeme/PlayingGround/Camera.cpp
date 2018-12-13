#include "Camera.h"
#include <GameThings\GlobalVariables.h>
#include <stdio.h>
namespace PlayingGround {

	Camera::Camera() : m_LocModel(0), m_LocView(0), m_LocProjection(0)
	{
	}


	Camera::~Camera()
	{
	}

	void Camera::init(glm::vec3 pos) {
		//m_view = glm::translate(m_view, glm::vec3(0.0f, 0.0f, -3.0f));
		m_projection = glm::perspective(45.0f, (float)GameThings::width / GameThings::height, 0.1f, 100.0f);
	//	m_model = glm::rotate(m_model, 45.0f, glm::vec3(0.5f, 1.0f, 0.0f));
	/*	m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		m_cameraDirection = glm::normalize(m_cameraPos - m_cameraTarget);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);*/
	//	m_cameraRight = glm::normalize(glm::cross(m_up, m_cameraDirection));
		m_view = glm::lookAt(pos,
							 glm::vec3(0.0f, 0.0f, 0.0f),
							 glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void Camera::update(GLuint pID, glm::vec3 pos) {
		m_cameraPos = pos;
		m_cameraFront = GameThings::cameraFront;
		m_cameraUp = GameThings::cameraUp;
		m_view = glm::lookAt(m_cameraPos, m_cameraFront + m_cameraPos , m_cameraUp);
		m_LocProjection = glGetUniformLocation(pID, "projection");
		glUniformMatrix4fv(m_LocProjection, 1, GL_FALSE, glm::value_ptr(m_projection));

		m_LocView = glGetUniformLocation(pID, "view");
		glUniformMatrix4fv(m_LocView, 1, GL_FALSE, glm::value_ptr(m_view));
		GameThings::projection = m_projection;
		GameThings::view = m_view;
	}
}