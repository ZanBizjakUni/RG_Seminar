#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"
#include "Player.h"


class Collision {
public:
	Collision();
	Collision(Player* plyr);
	~Collision();
	bool ifCollision(Entity entity);
	bool getCollision(){return collision; }
protected:
	bool collision;
	Player* m_plyr;
};