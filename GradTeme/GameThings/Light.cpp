#include "Light.h"
#include <GameThings\GlobalVariables.h>


Light::Light()
{
}


Light::~Light()
{
}

void Light::init(GLuint pID) {
	m_scale = 0.1;
	m_modelLoc = glGetUniformLocation(pID, "model");
	m_viewLoc = glGetUniformLocation(pID, "view");
	m_projecitonLoc = glGetUniformLocation(pID, "projection");


	m_model = glm::translate(m_model, m_position);
	m_model = glm::scale(m_model, glm::vec3(m_scale));
	//nastavimo barve kocke

}

void Light::update(PlayingGround::InputManager im) {
	if (m_isActive) {	
		m_model = glm::scale(m_model, glm::vec3(1 / m_scale));
		if (im.isKeyDown(GLFW_KEY_UP)) {
			m_position.y += m_speed ;
			m_model = glm::translate(m_model, glm::vec3(0.0f, m_speed, 0.0f));
		}
		if (im.isKeyDown(GLFW_KEY_DOWN)) {
			m_position.y -= m_speed;
			m_model = glm::translate(m_model, glm::vec3(0.0f, -m_speed, 0.0f));

		}
		if (im.isKeyDown(GLFW_KEY_LEFT)) {
			m_position.x -= m_speed;
			m_model = glm::translate(m_model, glm::vec3(-m_speed, 0.0f, 0.0f));
		}
		if (im.isKeyDown(GLFW_KEY_RIGHT)) {
			m_position.x += m_speed;
			m_model = glm::translate(m_model, glm::vec3(m_speed, 0.0f, 0.0f));
		}
		if (im.isKeyDown(GLFW_KEY_KP_8)) {
			m_position.z += m_speed;
			m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, m_speed));
		}
		if (im.isKeyDown(GLFW_KEY_KP_2)) {
			m_position.z -= m_speed;
			m_model = glm::translate(m_model, glm::vec3(0.0, 0.0f, -m_speed));
		}
		m_model = glm::scale(m_model, glm::vec3(m_scale));
		//printf("%f %f %f\n", m_position.x, m_position.y, m_position.z);
	}
	m_view = GameThings::view;
	m_projection = GameThings::projection;
	
}

void Light::draw(PlayingGround::SpriteBatch & spriteBatch, GLuint pID) {
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix4fv(m_projecitonLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	spriteBatch.draw(pID, "ourSampler0");
}
void Light::changeActivnes(bool reset) {
	if (reset) {
		m_isActive = false;
	}
	else {
		m_isActive ^= 1;
	}
}