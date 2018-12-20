#include "Camera.h"

namespace DEngine {

	Camera::Camera() {
		m_projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);

	}


	Camera::~Camera() {}

	void Camera::init() {
		m_pos = glm::vec3(0.0f, 0.0f, 3.0f);
		m_target = glm::vec3(0.0f, 0.0f, 0.0f);
		m_dir = glm::normalize(m_pos - m_target);

		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cRight = glm::normalize(glm::cross(m_up, m_dir));
		m_front = glm::vec3(0.0f, 0.0f, -1.0f);

		m_view = glm::lookAt(m_pos,
							 m_pos + m_front ,
							 m_up);
	}

	void Camera::update() {
		m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);

	}

}