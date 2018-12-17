#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include <Binder.h>


class Entity {
public:
	Entity();
	Entity(std::string bindName );
	~Entity();

	void draw(DEngine::Binder b);

protected:
	std::string m_bind;
};

