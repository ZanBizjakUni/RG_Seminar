#pragma once


#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "intersect.h"

class AABoundBox {
public:
	AABoundBox(const glm::vec3& minExtend, const glm::vec3& maxExtend) :
		m_minExtend(minExtend),
		m_maxExtend(maxExtend) {}

	Intersect IntersectAABB(const AABoundBox& other) const;

	inline const glm::vec3 getMinExtend() const { return m_minExtend; }
	inline const glm::vec3 getMaxExtend() const { return m_maxExtend; }
private:
	const glm::vec3 m_minExtend;
	const glm::vec3 m_maxExtend;
};