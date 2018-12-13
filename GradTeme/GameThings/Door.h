#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <PlayingGround\SpriteBatch.h>
class Door
{
public:
	Door();
	~Door();
	void init(GLint pID);
	void update();
	void draw(PlayingGround::SpriteBatch&);
private:
	glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_view;

	float m_speed = 0.1f;
	bool m_isOpen = false;
	GLfloat m_viewLoc;
	GLfloat m_modelLoc;
	GLfloat m_projectionLoc;

	glm::vec3 m_position;
};

