#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "DProps.h"

enum class Status { INAIR, ONGROUND, ONWALL };


namespace DEngine {

	class Physics {
	public:
		Physics();
		Physics(glm::vec3 pos);
		~Physics();
		void gravity(glm::vec3& pos);
		void gravity(glm::vec4& pos);
		void setColState(int c);
		void moveUp(glm::vec3& pos, glm::vec3 m_prevPos, float d);
		void moveUp(glm::vec4& pos, glm::vec4 m_prevPos);
		void setPrevColState();
		void update();
		void setBack(glm::vec3& pos, glm::vec3 prevPos,int d);
		void setBack(glm::vec4& pos, glm::vec3 prevPos);
	protected:
		float m_downVelocity;
		glm::vec3 m_bottomSphere;
		Status m_status;
		int m_colState;
		int m_prevColState;
	};	
}