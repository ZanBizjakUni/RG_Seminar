#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "DProps.h"

namespace DEngine {


	class Camera {
	public:
		Camera();
		~Camera();
		void init();
		glm::mat4 returnView() { return m_view; }
		glm::mat4 returnProjection() { return m_projection; }

		void update();
	private:
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::vec3 m_target;
		glm::vec3 m_dir;
		glm::vec3 m_cRight;
	protected:

		glm::vec3 m_up;
		glm::vec3 m_front;
		glm::vec3 m_pos;
	};

} //namespace