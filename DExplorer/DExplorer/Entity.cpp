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
}

void Entity::init(glm::vec4 p) {
	m_radius = 0.5;
	
	if (m_bind == "square") {
		m_minAABB = glm::vec4(p.x-m_radius, p.y-m_radius, p.z-0.1f, 1.0f);
		m_maxAABB = glm::vec4(p.x+m_radius, p.y+m_radius, p.z + 0.1f, 1.0f);
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y - m_radius, p.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y - m_radius, p.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y - m_radius, p.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y - m_radius, p.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y + m_radius, p.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y + m_radius, p.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y + m_radius, p.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y + m_radius, p.z - 0.1f, 1.0f));
	}
	m_model = glm::translate(m_model, glm::vec3(p.x, p.y, p.z));
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));
	m_selected = false;
	m_pos = p;
}

void Entity::draw(DEngine::Binder& b) {
	glBindVertexArray(b.getBinder(m_bind).VAO);
	if (b.getBinder(m_bind).indices.size() == 0) {
		glDrawArrays(GL_TRIANGLES, 0, 36);

	}
	else {
		glDrawElements(GL_TRIANGLES, b.getBinder(m_bind).indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void Entity::setColor(glm::vec3 clr) {
	m_color = clr;
}

void Entity::translate(glm::vec3 t) {
	m_model = glm::translate(m_model, t);
	m_pos = m_model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	//m_minAABB += glm::vec4(t, 0.0f);
	//m_maxAABB += glm::vec4(t, 0.0f);
	/*glm::vec4 tmp;
	m_minAABB -= glm::vec4(t, 1.0f);
	m_maxAABB -= glm::vec4(t, 1.0f);*/
	
	glm::vec4 tmp;
	m_minAABB = m_model * m_corners[0];
	m_maxAABB = m_model * m_corners[0];
	for (auto it : m_corners) {
		tmp = m_model * it;
		if (tmp.x < m_minAABB.x)
			m_minAABB.x = tmp.x;

		if (tmp.y < m_minAABB.y)
			m_minAABB.y = tmp.y;

		if (tmp.z < m_minAABB.z)
			m_minAABB.z = tmp.z;

		if (tmp.x > m_maxAABB.x)
			m_maxAABB.x = tmp.x;

		if (tmp.y > m_maxAABB.y)
			m_maxAABB.y = tmp.y;

		if (tmp.z > m_maxAABB.z)
			m_maxAABB.z = tmp.z;
	}
	for (auto it : m_children) {
		it->translate(t);
	}
	
}

void Entity::rotate(float deg, glm::vec3 axis) {
	
	m_model = glm::rotate(m_model, glm::radians(deg), axis);
	m_normalModel = glm::mat3(glm::transpose(glm::inverse(m_model)));

	glm::vec4 tmp;
	m_minAABB = m_model * m_corners[0];
	m_maxAABB = m_model * m_corners[0];
	for (auto it : m_corners) {
		tmp = m_model * it;
		if (tmp.x < m_minAABB.x)
			m_minAABB.x = tmp.x;
		
		if (tmp.y < m_minAABB.y)
			m_minAABB.y = tmp.y;
		
		if (tmp.z < m_minAABB.z)
			m_minAABB.z = tmp.z;

		if (tmp.x > m_maxAABB.x)
			m_maxAABB.x = tmp.x;
		
		if (tmp.y > m_maxAABB.y)
			m_maxAABB.y = tmp.y;
		
		if (tmp.z > m_maxAABB.z)
			m_maxAABB.z = tmp.z;
	}

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

void Entity::setRadius(int r) {
	m_radius = r;
}

void Entity::translateByParent(glm::mat4 parentMat) {
	
}

void Entity::select() {
	m_selected = true;
}

void Entity::unselect() {
	m_selected = false;
}
