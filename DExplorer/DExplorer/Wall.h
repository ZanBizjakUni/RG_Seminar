#pragma once
#include "TexturedEntity.h"

enum class Orientation { WALL, FLOOR };


class Wall: public TexturedEntity {
public:
	Wall();
	Wall(std::string bindName, glm::vec4 p) : TexturedEntity(bindName, p) {}
	~Wall();

	void setOrientation(Orientation o);
	Orientation getOrientation() { return m_ort; }
private:
	Orientation m_ort;
};

