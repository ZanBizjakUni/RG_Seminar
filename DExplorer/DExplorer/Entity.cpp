#include "Entity.h"


Entity::Entity() {}

Entity::Entity(std::string bindName, glm::vec4 p) {
	m_bind = bindName;
	m_textureless = true;
	m_color = glm::vec3(1.0f, 1.0f, 1.0f);
	init(p);
}



Entity::~Entity() {}

void Entity::init(glm::vec4 p) {
	m_model = glm::translate(m_model, glm::vec3(p.x, p.y, p.z));
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));

	m_orgPos = p;
	m_pos = p;
}

void Entity::draw(DEngine::Binder& b) {
	glBindVertexArray(b.getBinder(m_bind).VAO);
//	glDrawElements(GL_TRIANGLES, b.getBinder(m_bind).indices.size() , GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Entity::setColor(glm::vec3 clr) {
	m_color = clr;
}

void Entity::translate(glm::vec3 t) {
	t *= (float)DEngine::deltaTime;
	m_model = glm::translate(m_model, t);
	m_pos = m_model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	
}

void Entity::rotate(float deg, glm::vec3 axis) {
	m_model = glm::rotate(m_model, glm::radians(deg), axis);
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));
}

void Entity::scale(glm::vec3 scl) {
	m_model = glm::scale(m_model, scl);
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));

}

void Entity::lookAtPlayer(glm::vec3 u, glm::vec3 r) {
/*	glm::vec3 look = glm::normalize(p - glm::vec3(m_pos));
	glm::vec3 right = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), look);
	glm::vec3 up = glm::cross(look, right);
	glm::mat4 t;
	t[0] = glm::vec4(right.x, up.x, look.x, m_pos.x);
	t[1] = glm::vec4(right.y, up.y, look.y, m_pos.y);
	t[2] = glm::vec4(right.z, up.z, look.z, m_pos.z);
	m_model =  t;*/

}
