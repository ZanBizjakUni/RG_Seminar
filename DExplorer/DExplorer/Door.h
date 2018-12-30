#pragma once
#include "TexturedEntity.h"
class Door :public TexturedEntity{
public:
	Door();
	Door(std::string bindName, glm::vec4 p);
	~Door();
	void openClose();
private:
	bool m_isOpened;
};

