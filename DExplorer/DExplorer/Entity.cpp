#include "Entity.h"


Entity::Entity() {}

Entity::Entity(std::string bindName, glm::vec4 p) {
	m_bind = bindName;
	m_textureless = true;
	m_color = glm::vec3(1.0f, 1.0f, 1.0f);
	init(p);
}



Entity::~Entity() {}

void Entity::setRootEntity() {
	m_parentModel = m_model;
}

void Entity::init(glm::vec4 p) {
	m_model = glm::translate(m_model, glm::vec3(p.x, p.y, p.z));
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));

	m_orgPos = p;
	m_pos = p;
}

void Entity::draw(DEngine::Binder& b) {
	glBindVertexArray(b.getBinder(m_bind).VAO);
	glDrawElements(GL_TRIANGLES, b.getBinder(m_bind).indices.size() , GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Entity::setColor(glm::vec3 clr) {
	m_color = clr;
}

void Entity::translate(glm::vec3 t) {
	t *= (float)DEngine::deltaTime;
	m_model = glm::translate(m_model, t);
	m_pos = m_model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	t /= (float)DEngine::deltaTime;
	for (auto it : m_children) {
		it->translate(t);
	}
	
}

void Entity::rotate(float deg, glm::vec3 axis) {
	m_model = glm::rotate(m_model, glm::radians(deg), axis);
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));
	for (auto it : m_children) {
		it->rotate(deg, axis);
	}
}

void Entity::scale(glm::vec3 scl) {
	m_model = glm::scale(m_model, scl);
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));

}

void Entity::setChildren(Entity * child) {
	m_children.emplace_back(child);
}

void Entity::translateByParent(glm::mat4 parentMat) {
	m_parentModel = parentMat;
	
}
