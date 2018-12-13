#pragma once
#include <GL\glew.h>

#include <vector>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <PlayingGround\SpriteBatch.h>
class Menu
{
public:
	Menu();
	~Menu();
	std::vector<float> getVerts() { return m_menuVerecies; }
	void init(GLuint pID);
	void update();
	void drawS(PlayingGround::SpriteBatch & sb, GLuint pID);
	void drawE(PlayingGround::SpriteBatch & sb, GLuint pID);

private:

	glm::vec3 m_startPos;
	glm::vec3 m_exitPos;

	GLuint m_projecionLoc;
	GLuint m_viewLoc;
	GLuint m_modelLoc;

	glm::mat4 m_startModel;
	glm::mat4 m_exitModel;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	std::vector<float> m_menuVerecies = {
		-0.05f,  -0.15f, 0.0f,  0.0f, 0.0f,
		0.05f,  -0.15f, 0.0f,  1.0f, 0.0f,
		0.05f,  0.15f, 0.0f,  1.0f, 1.0f,
		0.05f,  0.15f, 0.0f,  1.0f, 1.0f,
		-0.05f,  0.15f, 0.0f,  0.0f, 1.0f,
		-0.05f,  -0.15f, 0.0f,  0.0f, 0.0f
	};
};

