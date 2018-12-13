#pragma once

#include "kocka.h"

class Collision
{
public:
	Collision();
	~Collision();

	void init(std::vector<kocka> EW, std::vector<kocka> NS);
	bool collisionCheck(glm::vec3 playerPos, bool& ori);

private:
	std::vector<kocka> proximityCheck(glm::vec3 playerPos);

	std::vector<kocka> m_walls;
	float m_radius = 1.1f;

};

