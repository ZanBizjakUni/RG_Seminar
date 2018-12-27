#pragma once


#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class AABoundBox {
public:
	AABoundBox() {};
	AABoundBox(glm::vec4 minExtend, glm::vec4 maxExtend) :
		m_maxExtend(maxExtend),
		m_minExtend(minExtend) {};
	~AABoundBox() {};


	//---entity bouding boxes---//
	inline glm::vec4 getMinExtend() const { return m_minExtend; }
	inline glm::vec4 getMaxExtend() const { return m_maxExtend; }
	inline void setMinExtend(glm::vec4 min) { m_minExtend = min; }
	inline void setMaxExtend(glm::vec4 max) { m_maxExtend = max; }
private:
	glm::vec4 m_minExtend;
	glm::vec4 m_maxExtend;
};