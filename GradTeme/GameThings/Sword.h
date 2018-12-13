#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <PlayingGround\SpriteBatch.h>


class Sword
{
public:
	Sword();
	~Sword();
	void init(GLuint pID, glm::vec3 pos);
	void update();
	void draw(PlayingGround::SpriteBatch& sb);
	std::vector<float> getVerts() { return m_vertecies; }
private:
	glm::vec3 m_position;
	GLuint m_pID;
	GLuint m_projecionLoc;
	GLuint m_viewLoc;
	GLuint m_modelLoc;
	std::vector<float> m_vertecies{
		-0.5f,  -0.5f, 0.0f,  0.0f, 0.0f,
		0.5f,  -0.5f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
		-0.5f,  -0.5f, 0.0f,  0.0f, 0.0f
	};
	glm::mat4 m_projection;
	glm::mat4 m_model;
	glm::mat4 m_view;
};

