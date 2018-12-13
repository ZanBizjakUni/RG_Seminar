#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <PlayingGround\SpriteBatch.h>
#include <PlayingGround\InputManager.h>
#include <PlayingGround\Vertex.h>

enum class Side { CEIL, FLOOR, SOUTH, NORTH, EAST, WEST };


class kocka
{
public:
	kocka();
	~kocka();
	void init(GLuint, glm::vec3);
	void update(PlayingGround::InputManager im);
	void draw(PlayingGround::SpriteBatch& spriteBatch, GLuint pID, glm::vec3);
	std::vector<float> getVerts() { return m_vertecies; }
	void indentify(Side);
	void moveFor(glm::vec3);
	void rotate();
	void changeActivnes(bool reset);
	glm::vec3 returnPosition() { return m_position; }
	Side returnSide() { return m_side; }
private:

	Side m_side;

	glm::vec3 m_objectColor;
	glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_view;

	float m_speed = 0.1f;
	bool m_isActive = false;
	GLfloat m_viewLoc;
	GLfloat m_modelLoc;
	GLfloat m_projectionLoc;
	GLfloat m_objectColorLoc;
	GLfloat m_lightColorLoc;
	GLfloat m_lightPosLoc;
	glm::vec3 m_position;
	std::vector<float> m_vertecies = {
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f
	};
};

