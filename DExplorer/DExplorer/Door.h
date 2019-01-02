#pragma once
#include "TexturedEntity.h"
class Door :public TexturedEntity{
public:
	Door();
	Door(std::ifstream& file);
	Door(std::string bindName, glm::vec4 p);
	~Door();
	void openClose();
	void writeToFile(std::ofstream& file);
private:
	bool m_isOpened;
};

