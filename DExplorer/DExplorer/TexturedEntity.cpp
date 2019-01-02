#include "TexturedEntity.h"



TexturedEntity::TexturedEntity() {}

TexturedEntity::TexturedEntity(std::ifstream & file) : Entity(file){
	int tmp;
	int size;
	file.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		file.read((char*)&tmp, sizeof(int));
		m_texBind.emplace_back();
		m_texBind.back().resize(tmp);
		file.read((char*)m_texBind.back().data(), tmp);
	}
}

TexturedEntity::TexturedEntity(std::string bindName, glm::vec4 p): Entity(bindName, p) {
	m_textureless = false;
}




TexturedEntity::~TexturedEntity() {
}

void TexturedEntity::setTexBind(std::string texBind) {
	m_texBind.emplace_back(texBind);
	m_texBind.back().shrink_to_fit();
}

void TexturedEntity::draw(DEngine::Binder& b) {
	for (GLubyte i = 0; i < m_texBind.size(); i++) { 
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, b.getTextureBinder(m_texBind[i]));
	}

	
	Entity::draw(b);
}

void TexturedEntity::writeToFile(std::ofstream & file) {
	Entity::writeToFile(file);
	int tmp;
	tmp = (int)m_texBind.size();
	file.write((char*)&tmp, sizeof(int));
	for (auto it : m_texBind) {
		tmp = it.size();
		file.write((char*)&tmp, sizeof(int));
		file.write((char*)it.c_str(), tmp);

	}
}
