#include <cmath>

#include "AABoundBox.h"

Intersect AABoundBox::IntersectAABB(const AABoundBox& other) const
{
	/*m::vec3 distances1 = other.getMinExtend - m_maxExtend;
	glm::vec3 distances2 = m_minExtend - other.getMaxExtend;
	glm::vec3 distances = glm::vec3(fmax(distances1.x, distances.x), fmax(distances1.y, distances.y), fmax(distances1.z, distances.z));

	float maxDistance = fmax(distances.z, fmax(distances.x, distances.y));

	return Intersect(maxDistance < 0, maxDistance);*/
	return Intersect(0, 0);
}