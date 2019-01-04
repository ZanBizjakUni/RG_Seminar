#include "Physics.h"

namespace DEngine {
	Physics::Physics() {}
	Physics::Physics(glm::vec3 pos) {

		m_status = Status::INAIR;
		m_downVelocity = 0.0f;
		m_colState = -1;
		m_prevColState = m_colState;
		m_bottomSphere = pos - glm::vec3(0.0f, 0.3f, 0.0f);

	}


	Physics::~Physics() {}

	void Physics::gravity(glm::vec3& pos) {
		if (m_colState == -1 || m_colState == 2) {
			m_downVelocity += DEngine::gravity * deltaTime;
		}


		pos.y -= m_downVelocity;
		m_bottomSphere.y -= m_downVelocity;
	}

	void Physics::gravity(glm::vec4 & pos) {
		if (m_colState == -1 || m_colState == 2) {
			m_downVelocity += DEngine::gravity * deltaTime;
		}


		pos.y -= m_downVelocity;
		m_bottomSphere.y -= m_downVelocity;
	}

	void Physics::setColState(int c) {
		m_colState = c;
	}
	void Physics::moveUp(glm::vec3 & pos, glm::vec3 m_prevPos, float d) {
		pos.y+=d;
		m_downVelocity = 0;
		m_bottomSphere.y = pos.y - 0.3f;
	}
	void Physics::moveUp(glm::vec4 & pos, glm::vec4 m_prevPos) {
		pos.y = m_prevPos.y;
		m_downVelocity = 0;
		m_bottomSphere.y = pos.y - 0.3f;
	}

	void Physics::setPrevColState() {
		m_prevColState = m_colState;
	}
	void Physics::update() {
		if ((m_colState == -1 && m_prevColState == 2) || (m_colState == 2 && m_prevColState == -1)) {
			m_status = Status::ONGROUND;
		}
		else if ((m_colState == 3 || m_colState == 1) && m_prevColState == -1) {
			m_status = Status::ONWALL;
		}
		else if (m_colState == -1 && m_prevColState == -1) {
			m_status = Status::INAIR;
		}

		if (m_prevColState == -1 && (m_colState == 1 || m_colState == 3)) {
			m_downVelocity = 0;
		}
	}
	void Physics::setBack(glm::vec3 & pos, glm::vec3 prevPos, int d) {
		switch (d) {
		case 1:
			pos = glm::vec3(prevPos.x, pos.y, pos.z);
			break;
		case 2:
			pos = glm::vec3(pos.x, prevPos.y, pos.z);
			break;
		case 3:
			pos = glm::vec3(pos.x, pos.y, prevPos.z);
			break;
		}
		m_bottomSphere = pos - glm::vec3(0.0f, 0.3f, 0.0f);
	}
	void Physics::setBack(glm::vec4 & pos, glm::vec3 prevPos) {
		switch (m_colState) {
		case 1:
			pos = glm::vec4(prevPos.x, pos.y, pos.z, 1.0f);
			break;
		case 2:
			pos = glm::vec4(pos.x, prevPos.y, pos.z, 1.0f);
			break;
		case 3:
			pos = glm::vec4(pos.x, pos.y, prevPos.z, 1.0f);
			break;
		}
		m_bottomSphere = pos - glm::vec4(0.0f, 0.3f, 0.0f, 0.0f);
	}
}//namespace