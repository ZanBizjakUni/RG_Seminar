#include "Sword.h"
#include "GlobalVariables.h"


Sword::Sword()
{
}


Sword::~Sword()
{
}

void Sword::init(GLuint pID, glm::vec3 pos){
	m_position = pos;
	m_pID = pID;
	m_projecionLoc = glGetUniformLocation(pID, "projection");
	m_viewLoc = glGetUniformLocation(pID, "view");
	m_modelLoc = glGetUniformLocation(pID, "model");
	m_model = glm::translate(m_model, m_position);
}

void Sword::update(){
	m_view = GameThings::view;
	m_projection = GameThings::projection;
}

void Sword::draw(PlayingGround::SpriteBatch& sb){
	glUniformMatrix4fv(m_projecionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
	sb.draw(m_pID, "ourSampler");
}
