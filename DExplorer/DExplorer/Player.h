#pragma once
#include <Camera.h>
#include <DProps.h>
#include <vector>

enum class Direction{FORWARD, BACKWARD, LEFT, RIGHT};

class Player: public DEngine::Camera {
public:
	Player();
	~Player();
	void move(Direction d);
	void toggleSprint();
	void unToggleSprint();
	void update(glm::vec2 offset);
	float getYaw() { return m_yaw; }
	void setBack(int d);
	glm::vec3 getLookingAt() { return m_pos + m_front; }
	glm::vec3 getMinAABB() { return m_minAABB; }
	glm::vec3 getMaxAABB() { return m_maxAABB; }
private:
	double m_move;
	glm::vec3 m_prevPos;
	std::vector<glm::vec4> m_corners;
	glm::vec3 m_maxAABB;
	glm::vec3 m_minAABB;
	float m_speed;
	bool m_sprint;
	float m_yaw;
	float m_pitch;
	float m_stepLen;
	float m_stepHeight;
	
};

