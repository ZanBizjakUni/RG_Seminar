#include "CollisionManager.h"


namespace DEngine {
	CollisionManager::CollisionManager() {}


	CollisionManager::~CollisionManager() {}

	int CollisionManager::checkCollision(glm::vec3 aMinAABB, glm::vec3 aMaxAABB, glm::vec3 bMinAABB, glm::vec3 bMaxAABB) {
		if (aMinAABB.x <= bMaxAABB.x && aMaxAABB.x >= bMinAABB.x) {
			float x = std::abs(aMinAABB.x - bMaxAABB.x);
			if (x >= std::abs(bMinAABB.x - aMaxAABB.x)) {
				x = std::abs(bMinAABB.x - aMaxAABB.x);
			}
			if (aMinAABB.y <= bMinAABB.y && aMaxAABB.y >= bMinAABB.y) {
				float y = std::abs(aMinAABB.y - bMaxAABB.y);
				if (y >= std::abs(bMinAABB.y - aMaxAABB.y)) {
					y = std::abs(bMinAABB.y - aMaxAABB.y);
				}
				if (aMinAABB.z <= bMaxAABB.z && aMaxAABB.z >= bMinAABB.z) {
					float z = std::abs(aMinAABB.z- bMaxAABB.z);
					if (z >= std::abs(bMinAABB.z - aMaxAABB.z)) {
						z = std::abs(bMinAABB.z - aMaxAABB.z);
					}
					float min = std::fminf(x, y);
					min = std::fminf(min, z);
					if (min == x) {
						return 1;
					}
					else if (min == y) {
						return 2;
					}
					else if (min == z) {
						return 3;
					}
				}
			}
		}

		return -1;
	}

	bool CollisionManager::pointCollision(glm::vec3 p, glm::vec3 minAABB, glm::vec3 maxAABB) {
		/*if (p.x > minAABB.x && p.x < maxAABB.x) {
			if (p.y > minAABB.y && p.y < maxAABB.y) {
				if (p.z > minAABB.z && p.z < maxAABB.z) {
					return true;
				}
			}
		}
		return false;*/
		float x = std::fmaxf(minAABB.x, std::fminf(p.x, maxAABB.x));
		float y = std::fmaxf(minAABB.y, std::fminf(p.y, maxAABB.y));
		float z = std::fmaxf(minAABB.z, std::fminf(p.z, maxAABB.z));
		glm::vec3 d = glm::vec3(x, y, z);
		float dist = glm::distance(d, p);

		return dist < 0.2f;
		
	}

}