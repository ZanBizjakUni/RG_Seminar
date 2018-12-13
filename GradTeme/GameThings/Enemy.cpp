#include "Enemy.h"
#include "GlobalVariables.h"
#include <math.h>

#define M_PI           3.14159265358979323846

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::init(glm::vec3 pos, GLuint pID){
	printf("position: %g %g\n", pos.x, pos.z);

	m_position = glm::vec3(pos.x+0.3f, pos.y, pos.z+0.3f);
	m_prevPos = m_position;
	m_pID = pID;
	m_damageLoc = glGetUniformLocation(pID, "damaged");
	m_projecionLoc = glGetUniformLocation(pID, "projection");
	m_viewLoc = glGetUniformLocation(pID, "view");
	m_modelLoc = glGetUniformLocation(pID, "model");
	m_model = glm::translate(m_model, m_position);

	m_offset = 0;
	m_k = (pos.z - m_position.z) / (pos.x - m_position.x);
	m_k = (1 / m_k);
	m_angle = atan(m_k);
	m_model = glm::rotate(m_model, m_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	m_globalOffset = m_angle;
}

void Enemy::update(glm::vec3 curPos, glm::vec3 prevPos, Collision* col){
	m_speed = m_defSpeed * GameThings::deltaTime;
	if (!m_isStunned) {
		calcPosition(curPos, prevPos);

		float tmp = fmod(m_globalOffset, 2 * M_PI);
		m_model = glm::rotate(m_model, -tmp, glm::vec3(0.0f, 1.0f, 0.0f));

		if (col->collisionCheck(m_position, m_ori)) {
			if (m_ori) {
				m_position.z = m_prevPos.z;
			}
			else {
				m_position.x = m_prevPos.x;
			}
		}
		else {
			move(curPos, prevPos);
		}
		m_model = glm::rotate(m_model, tmp, glm::vec3(0.0f, 1.0f, 0.0f));
		m_model = glm::rotate(m_model, m_offset, glm::vec3(0.0f, 1.0f, 0.0f));

		m_prevPos = m_position;
	}
	else {
		if (glfwGetTime() - m_stunStart >= 0.5f) {
			m_isStunned = false;
		}
	}
	m_view = GameThings::view;
	m_projection = GameThings::projection;
}

void Enemy::draw(PlayingGround::SpriteBatch & sb, GLuint pID){
	glUniformMatrix4fv(m_projecionLoc, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_viewLoc, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(m_modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
	glUniform1i(m_damageLoc,m_isStunned);
	glUniform3f(m_lightColorLoc, 1.0f, 1.0f, 1.0f);
	glUniform3f(m_lightPosLoc, 1.0f, 1.5f, 0.5f);
	sb.draw(pID, "ourSampler");
}

void Enemy::getHit(){
	m_health -= 1;
	m_stunStart = glfwGetTime();
	m_isStunned = true;
}

bool Enemy::isDead()
{
	if (m_health <= 0) {
		return true;
	}
	return false;
}

double Enemy::calcOffset(glm::vec3 curPos, glm::vec3 prevPos) {

	double angle;
	double k1;
	double k2;
	k1 = (prevPos.z - m_position.z) / (prevPos.x - m_position.x);
	k2 = (curPos.z - m_position.z) / (curPos.x - m_position.x);
	k1 = -(1 / k1);
	k2 = -(1 / k2);
	angle = (k1 - k2) / (1 + (k1 * k2));
	angle = atan(angle);
	return angle;
}

void Enemy::move(glm::vec3 curPos, glm::vec3 prevPos){
	if (m_k < 0) {

		if (curPos.z < m_position.z) {
			m_model = glm::translate(m_model, glm::vec3(m_speed * cos(m_angle), 0.0f, 0.0f));
			m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, -m_speed * sin(m_angle)));
		}
		else {
			m_model = glm::translate(m_model, glm::vec3(-m_speed * cos(m_angle), 0.0f, 0.0f));
			m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, m_speed * sin(m_angle)));
		}
	}
	else {
		if (curPos.z < m_position.z) {
			m_model = glm::translate(m_model, glm::vec3(-m_speed * cos(m_angle), 0.0f, 0.0f));
			m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, -m_speed * sin(m_angle)));
		}
		else {
			m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, m_speed * sin(m_angle)));
			m_model = glm::translate(m_model, glm::vec3(m_speed * cos(m_angle), 0.0f, 0.0f));
		}
	}

}

void Enemy::calcPosition(glm::vec3 curPos, glm::vec3 prevPos){

	m_offset = calcOffset(curPos, prevPos);
	m_k = (curPos.z - m_position.z) / (curPos.x - m_position.x);
	m_angle = abs(atan(m_k));
	m_globalOffset += m_offset;

	if (m_k < 0) {

		if (curPos.z < m_position.z) {
			m_position.x += (m_speed)* cos(m_angle);
			m_position.z += -m_speed * sin(m_angle);
		}
		else {
			m_position.x += -(m_speed)* cos(m_angle);
			m_position.z += m_speed * sin(m_angle);
		}
	}
	else {
		if (curPos.z < m_position.z) {
			m_position.x += -(m_speed)* cos(m_angle);
			m_position.z += -m_speed * sin(m_angle);
		}
		else {
			m_position.x += (m_speed)* cos(m_angle);
			m_position.z += m_speed * sin(m_angle);
		}
	}
}
