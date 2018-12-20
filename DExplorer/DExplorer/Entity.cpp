#include "Entity.h"


Entity::Entity() {}

Entity::Entity(std::string bindName, glm::vec4 p) {
	m_bind = bindName;
	init(p);
}



Entity::~Entity() {}

void Entity::init(glm::vec4 p) {
	m_model = glm::translate(m_model, glm::vec3(p.x, p.y, p.z));
	m_pos = p;
}

void Entity::draw(DEngine::Binder& b) {
	glBindVertexArray(b.getBinder(m_bind).VAO);
	glDrawElements(GL_TRIANGLES, b.getBinder(m_bind).indices.size() , GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Entity::translate(glm::vec3 t) {
	m_model = glm::translate(m_model, t);
	m_pos = m_model * m_pos;
}

void Entity::rotate(float deg, glm::vec3 axis) {
	m_model = glm::rotate(m_model, glm::radians(deg), axis);
}

void Entity::scale(glm::vec3 scl) {
	m_model = glm::scale(m_model, scl);
}
