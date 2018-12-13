#include "kocka.h"
#include "GlobalVariables.h" 
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
kocka::kocka(){

}


kocka::~kocka()
{
}

void kocka::init( GLuint pID, glm::vec3 pos){

	m_modelLoc = glGetUniformLocation(pID, "model");
	m_viewLoc = glGetUniformLocation(pID, "view");
	m_projectionLoc = glGetUniformLocation(pID, "projection");
	m_lightColorLoc = glGetUniformLocation(pID, "lightColor");
	m_lightPosLoc = glGetUniformLocation(pID, "lightPos");
//	m_view = glm::translate(m_view, m_position);
	//nastavimo barve kocke
	glUniform3f(m_lightColorLoc, 1.0f, 1.0f, 1.0f);
	m_position = pos;
	m_model = glm::translate(m_model, m_position);
}

void kocka::update(PlayingGround::InputManager im){
	m_view = GameThings::view;
	m_projection = GameThings::projection;
}

void kocka::draw(PlayingGround::SpriteBatch & spriteBatch, GLuint pID, glm::vec3 lightPos) {


	glUniformMatrix4fv(m_projectionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
	glUniform3f(m_lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	spriteBatch.draw(pID, "ourSampler");
}
void kocka::indentify(Side side){
	m_side = side;
	std::string sideDir;
	std::ifstream file("Assets/wallVerts.txt");
	m_vertecies.clear();
	if (file.fail()) {
		printf("Failed to open file!\n");
	}
	switch (m_side) {
	case Side::CEIL:
		sideDir = "FC";
		m_position += glm::vec3(0.0f, 2.0f, 0.0f);
		m_model = glm::translate(m_model, glm::vec3(0.0f, 2.0f, 0.0f));
		break;
	case Side::FLOOR:
		sideDir = "FC";
		break;
	case Side::EAST:
		sideDir = "EW";
		m_position += glm::vec3(1.0f, 0.0f, 0.0f);
		m_model = glm::translate(m_model, glm::vec3(1.0f, 0.0f, 0.0f));
		break;
	case Side::WEST:
		sideDir = "EW";
		m_position += glm::vec3(-1.0f, 0.0f, 0.0f);
		m_model = glm::translate(m_model, glm::vec3(-1.0f, 0.0f, 0.0f));
		break;
	case Side::NORTH:
		sideDir = "SN";
		m_position += glm::vec3(0.0f, 0.0f, -1.0f);
		m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, -1.0f));
		break;
	case Side::SOUTH:
		sideDir = "SN";
		m_position += glm::vec3(0.0f, 0.0f, 1.0f);
		m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, 1.0f));
		break;
	}
	std::string tmp;
	while (!file.eof()) {
		file >> tmp;
		if (tmp == sideDir) {
			//printf("find successul, side = %d\n", m_side);
			break;
		}
	}
	for (int i = 0; i < 30; i++) {
		file >> tmp;
		m_vertecies.push_back(stof(tmp));
	}
	for (auto it : m_vertecies) {
	}
	file.close();
}
void kocka::moveFor(glm::vec3 position){
	m_model = glm::translate(m_model, position);
	m_position += position;
}
void kocka::rotate(){
	float rotat =89.0f;
	double a = 0.999847695;
	double b = 0.982547593;
	if (m_isActive) {
		a *= -1;
	//	b *= -1;
		rotat = 271.0f;
	}
	switch (m_side) {
	case Side::EAST:
		if (m_isActive) {
			m_position += glm::vec3(-a, 0.0f, -b);
		}
		m_model = glm::translate(m_model, glm::vec3(-a, 0.0f, b));
		m_model = glm::rotate(m_model, glm::radians(rotat), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case Side::WEST:
		if (m_isActive) {
			m_position += glm::vec3(a, 0.0f, b);
		}
		m_model = glm::translate(m_model, glm::vec3(a, 0.0f, -b));
		m_model = glm::rotate(m_model, glm::radians(rotat), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case Side::NORTH:
		if (m_isActive) {
			m_position += glm::vec3(-b, 0.0f, a);
		}
		m_model = glm::translate(m_model, glm::vec3(b, 0.0f, a));
		m_model = glm::rotate(m_model, glm::radians(rotat), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case Side::SOUTH:
		if (m_isActive) {
			m_position += glm::vec3(b, 0.0f, -a);
		}
		m_model = glm::translate(m_model, glm::vec3(-b, 0.0f, -a));
		m_model = glm::rotate(m_model, glm::radians(rotat ), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	}
	
}
void kocka::changeActivnes(bool reset){
	if (reset) {
		m_isActive = false;
	}
	else {
		m_isActive ^= 1;
	}
}

