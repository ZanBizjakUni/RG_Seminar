#pragma once

#include <glm/glm.hpp>
#include <math.h>
namespace DEngine {
	class CollisionManager {
	public:
		CollisionManager();
		~CollisionManager();
		int checkCollision(glm::vec3 aMinAABB, glm::vec3 aMaxAABB, glm::vec3 bMinAABB, glm::vec3 bMaxAABB);
		bool pointCollision(glm::vec3 p, glm::vec3 minAABB, glm::vec3 maxAABB);
	};

}