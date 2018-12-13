#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <PlayingGround\SpriteBatch.h>
#include "Collision.h"


class Enemy
{
public:
	Enemy();
	~Enemy();
	void init(glm::vec3, GLuint);
	void update(glm::vec3 curPos, glm::vec3 prevPos, Collision* col);
	void draw(PlayingGround::SpriteBatch&, GLuint);
	std::vector<float> getVerts() { return m_vertecies; }
	glm::vec3 returnPosition() { return m_position; }
	void getHit();
	bool isDead();
private:
	double calcOffset(glm::vec3 curPos, glm::vec3 prevPos);
	void move(glm::vec3 curPos, glm::vec3 prevPos);
	void calcPosition(glm::vec3 curPos, glm::vec3 prevPos);
	glm::vec3 m_position;
	glm::vec3 m_prevPos;
	GLuint m_pID;
	GLuint m_damageLoc;
	GLuint m_projecionLoc;
	GLuint m_viewLoc;
	GLuint m_modelLoc;
	GLuint m_lightColorLoc;
	GLuint m_lightPosLoc;
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
	float m_k;
	float m_angle;
	float m_defSpeed = 0.75f;
	float m_speed = 0.01f;
	float m_globalOffset;
	float m_offset;
	bool m_ori = true;
	bool m_isStunned = false;
	int m_health = 2;
	float m_stunStart = 0;

};

