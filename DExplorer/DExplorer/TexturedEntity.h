#pragma once

#include <vector>

#include "Entity.h"

class TexturedEntity: public Entity {
public:
	TexturedEntity();
	TexturedEntity(std::string bindName);
	~TexturedEntity();
	std::vector<std::string> getTex() { return m_texBind; }
	void setTexBind(std::string texBind);
	void draw(DEngine::Binder& b);
protected:
	std::vector<std::string> m_texBind;
};

