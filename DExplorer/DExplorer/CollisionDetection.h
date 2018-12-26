#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Entity.h"
#include "Player.h"


class CollisionDetection {
public:
	bool getCollision();

protected:
	bool collision;

};
