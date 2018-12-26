#pragma once

#include <vector>
#include <array>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Binder.h>
#include <DProps.h>


class Entity {
public:
	Entity();
	Entity(std::string bindName, glm::vec4 p);
	~Entity();

	void setRootEntity();
	void init(glm::vec4 p);
	void draw(DEngine::Binder& b);
	glm::mat4 returnTransMat() { return m_model; }
	glm::mat3 getNormModel() { return m_normalModel; }
	void setColor(glm::vec3 clr);
	glm::vec3 getColor() { return m_color; }
	void translate(glm::vec3 t);
	void rotate(float deg, glm::vec3 axis);
	void scale(glm::vec3 scl);
	glm::vec3 getPos() { return glm::vec3(m_pos); }
	bool isTextureless() { return m_textureless; }
	void setChildren(Entity* child);
	void setRadius(int r);
	void translateByParent(glm::mat4 parentMat);
	bool isSeleced() { return m_selected; }
	void select();
	void unselect();
protected:
	int m_radius;
	std::string m_bind;
	glm::vec4 m_pos;
	glm::vec4 m_orgPos;
	glm::mat4 m_model;
	glm::mat4 m_parentModel;
	glm::mat3 m_normalModel;
	bool m_textureless;
	bool m_selected;
	std::vector<Entity*> m_children;
private:

	glm::vec3 m_color;
};

