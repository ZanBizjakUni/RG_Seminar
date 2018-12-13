#include "Menu.h"
#include <GameThings\GlobalVariables.h>


Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::init(GLuint pID){
	m_exitPos = glm::vec3(0.0f, 0.4f, 0.0f);
	m_startPos = glm::vec3(0.0f, -0.4f, 0.0f);

	m_projecionLoc = glGetUniformLocation(pID, "projection");
	m_viewLoc = glGetUniformLocation(pID, "location");
	m_modelLoc = glGetUniformLocation(pID, "model");

	m_startModel = glm::translate(m_startModel, m_startPos);
	m_exitModel = glm::translate(m_exitModel, m_exitPos);
	m_projection = glm::perspective(45.0f, (float)GameThings::width / GameThings::height, 0.1f, 100.0f);
	m_view = glm::lookAt(glm::vec3(0.0f,0.0f,1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void Menu::update() {

}

void Menu::drawS(PlayingGround::SpriteBatch & sb, GLuint pID){
	glUniformMatrix4fv(m_projecionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_startModel));
	sb.draw(pID, "ourSampler");
}

void Menu::drawE(PlayingGround::SpriteBatch & sb, GLuint pID) {
	glUniformMatrix4fv(m_projecionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_exitModel));
	sb.draw(pID, "ourSampler");
}

