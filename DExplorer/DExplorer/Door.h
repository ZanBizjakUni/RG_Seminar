#pragma once
#include "Wall.h"
class Door :public Wall{
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

