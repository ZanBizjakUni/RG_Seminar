#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Binder.h>


class Entity {
public:
	Entity();
	Entity(std::string bindName, glm::vec4 p);
	~Entity();

	void init(glm::vec4 p);
	void draw(DEngine::Binder& b);
	glm::mat4 returnTransMat() { return m_model; }
	
	void translate(glm::vec3 t);
	void rotate(float deg, glm::vec3 axis);
	void scale(glm::vec3 scl);
	
protected:
	std::string m_bind;
	glm::vec4 m_pos;
	glm::mat4 m_model;

};

