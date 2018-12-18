#include "TexturedEntity.h"



TexturedEntity::TexturedEntity() {}

TexturedEntity::TexturedEntity(std::string bindName) {
	m_bind = bindName;
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
		glBindTexture(GL_TEXTURE, b.getTextureBinder(m_texBind[i]));
	}
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, b.getTextureBinder(m_texBind[0]));

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, b.getTextureBinder(m_texBind[1]));
	
	Entity::draw(b);
}
