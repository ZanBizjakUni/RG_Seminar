#pragma once
#include <Camera.h>
#include <DProps.h>
#include <vector>

enum class Direction{FORWARD, BACKWARD, LEFT, RIGHT};

enum class Status{INAIR, ONGROUND, ONWALL};

enum class PState{PLAY, CREATE};

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
	void setColState(int c);
	void setPrevColState();
	void setPrevPos();
	void moveUp(float d);
	void jump();
	glm::vec3 getLookingAt() { return m_pos + m_front; }
	glm::vec3 getMinAABB() { return m_minAABB; }
	glm::vec3 getMaxAABB() { return m_maxAABB; }
	glm::vec3 getSphere() { return m_bottomSphere; }
	void gravity();
	PState getState() { return m_state; }
	void setState(PState s);
private:
	double m_move;
	glm::vec3 m_prevPos;
	glm::vec3 m_bottomSphere;
	std::vector<glm::vec4> m_corners;
	glm::vec3 m_maxAABB;
	glm::vec3 m_minAABB;
	float m_speed;
	float m_downVelocity;
	bool m_sprint;
	float m_yaw;
	float m_pitch;
	float m_stepLen;
	float m_stepHeight;
	int m_colState;
	int m_prevColState;
	Status m_status;
	PState m_state;
	
};

