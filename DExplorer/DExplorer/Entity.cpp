#include "Entity.h"


Entity::Entity() {}

Entity::Entity(std::string bindName) {
	m_bind = bindName;
}



Entity::~Entity() {}

void Entity::draw(DEngine::Binder b) {
	glBindVertexArray(b.getBinder(m_bind).VAO);
	glDrawElements(GL_TRIANGLES, b.getBinder(m_bind).indices.size() , GL_UNSIGNED_INT, 0);
}
