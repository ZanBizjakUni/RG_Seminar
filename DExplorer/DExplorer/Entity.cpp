#include "Entity.h"


Entity::Entity() {}

Entity::Entity(std::string bindName, glm::vec4 p) {
	m_bind = bindName;
	m_textureless = true;
	m_color = glm::vec3(0.0f, 0.0f, 0.0f);

	init(p);
}

Entity::Entity(std::ifstream & file) {
	int tmp;
	file.read((char*)&m_radius, sizeof(float));
	file.read((char*)&tmp, sizeof(int));

	m_bind.resize(tmp);
	file.read((char*)m_bind.data(), tmp);
	file.read((char*)glm::value_ptr(m_pos), 4 * sizeof(float));
	file.read((char*)glm::value_ptr(m_minAABB), 4 * sizeof(float));
	file.read((char*)glm::value_ptr(m_maxAABB), 4 * sizeof(float));
	file.read((char*)&tmp,sizeof(int));
	for (int i = 0; i < tmp; i++) {
		glm::vec4 a;
		file.read((char*)glm::value_ptr(a),4 * sizeof(float));
		m_corners.emplace_back(a);
	}
	file.read((char*)glm::value_ptr(m_model), 16 * sizeof(float));
	file.read((char*)glm::value_ptr(m_normalModel), 9 * sizeof(float));
	file.read((char*)&m_textureless, sizeof(bool));
	file.read((char*)&m_selected, sizeof(bool));
	file.read((char*)glm::value_ptr(m_color), 3 * sizeof(float));
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
	else if (m_bind == "cube") {
		m_minAABB = glm::vec4(p.x - m_radius, p.y - m_radius, p.z - m_radius, 1.0f);
		m_maxAABB = glm::vec4(p.x + m_radius, p.y + m_radius, p.z + m_radius, 1.0f);
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y - m_radius, p.z + m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y - m_radius, p.z + m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y - m_radius, p.z - m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y - m_radius, p.z - m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y + m_radius, p.z + m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y + m_radius, p.z + m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x + m_radius, p.y + m_radius, p.z - m_radius, 1.0f));
		m_corners.emplace_back(glm::vec4(p.x - m_radius, p.y + m_radius, p.z - m_radius, 1.0f));
	}
	else if (m_bind == "skeleton") {
		m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y + 0.1f, m_pos.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z + 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x + 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
		m_corners.emplace_back(glm::vec4(m_pos.x - 0.1f, m_pos.y - 0.5f, m_pos.z - 0.1f, 1.0f));
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

void Entity::writeToFile(std::ofstream & file) {
	int tmp;
	file.write((char*)&m_radius, sizeof(float));
	tmp = m_bind.size();
	file.write((char*)&tmp, sizeof(int));
	file.write((char*)m_bind.c_str(), m_bind.size());
	DEngine::FileManager::write4f(file, m_pos);
	DEngine::FileManager::write4f(file, m_minAABB);
	DEngine::FileManager::write4f(file, m_maxAABB);
	tmp = (int)m_corners.size();
	file.write((char*)&tmp, sizeof(int));
	for (auto it : m_corners) {
		DEngine::FileManager::write4f(file, it);
	}
	DEngine::FileManager::writeM4(file, m_model);
	DEngine::FileManager::writeM3(file, m_normalModel);

	file.write((char*)&m_textureless, sizeof(bool));
	file.write((char*)&m_selected, sizeof(bool));
	DEngine::FileManager::write3f(file, m_color);
}
