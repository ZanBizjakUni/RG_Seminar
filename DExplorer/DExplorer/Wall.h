#pragma once
#include "TexturedEntity.h"

enum class WallType { WALL, FLOOR };

enum class Orientation{NORTH, SOUTH, EAST, WEST, UP, DOWN};


class Wall: public TexturedEntity {
public:
	Wall();
	Wall(std::ifstream& file);
	Wall(std::string bindName, glm::vec4 p);
	~Wall();

	void setType(WallType o);
	void setOrientation(Orientation o);

	WallType getType() { return m_type; }
	Orientation getOrientation() { return m_orientation; }
	void writeToFile(std::ofstream& file);
private:
	Orientation m_orientation;
	WallType m_type;
};

