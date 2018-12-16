#pragma once

#include <vector>
#include <array>
#include <algorithm>

class Entity {
public:
	Entity();
	Entity(float verts[] );

	~Entity();
protected:
	std::vector<float> m_verts;
};

