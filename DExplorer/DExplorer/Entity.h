#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Binder.h>
#include <DProps.h>
#include <FileManager.h>


class Entity {
public:
	Entity();
	Entity(std::string bindName, glm::vec4 p);
	Entity(std::ifstream& file);
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
	int getRadius() { return m_radius; }
	std::string getBind() { return m_bind; }
	void translateByParent(glm::mat4 parentMat);
	bool isSeleced() { return m_selected; }
	void select();
	void unselect();
	glm::vec3 getMinAABB() { return m_minAABB; }
	glm::vec3 getMaxAABB() { return m_maxAABB; }
	glm::vec3 getTransformedMinAABB() { return m_model * m_minAABB; }
	glm::vec3 getTransformedMaxAABB() { return m_model * m_maxAABB; }
	void writeToFile(std::ofstream& file);
protected:
	float m_radius;
	std::string m_bind;
	glm::vec4 m_pos;
	glm::vec4 m_minAABB;
	glm::vec4 m_maxAABB;
	std::vector<glm::vec4> m_corners;
	glm::mat4 m_model;
	glm::mat3 m_normalModel;
	bool m_textureless;
	bool m_selected;
	std::vector<Entity*> m_children;
private:

	glm::vec3 m_color;
};

