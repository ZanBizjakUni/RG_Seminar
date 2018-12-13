#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

namespace PlayingGround {

	class Camera
	{
	public:
		Camera();
		~Camera();
		void init(glm::vec3);
		void update(GLuint pID, glm::vec3);
		glm::vec3 returnLookAt() { return m_cameraFront+m_cameraPos ; }
	private:
		glm::mat4 m_model;
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::vec3 m_cameraPos;
		glm::vec3 m_cameraFront;
		glm::vec3 m_cameraTarget;
		glm::vec3 m_cameraDirection;
		glm::vec3 m_up;
		glm::vec3 m_cameraRight;
		glm::vec3 m_cameraUp;

		GLuint m_LocModel;
		GLuint m_LocView;
		GLuint m_LocProjection;
	};

} //namespace