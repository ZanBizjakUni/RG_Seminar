#pragma once
#include <Camera.h>
#include <DProps.h>

enum class Direction{FORWARD, BACKWARD, LEFT, RIGHT};

class Player: public DEngine::Camera {
public:
	Player();
	~Player();
	void move(Direction d);
	void toggleSprint();
	void unToggleSprint();
	void update(glm::vec2 offset);
	void goBack() { m_pos = m_prevPos; };
	float getYaw() { return m_yaw; }
private:
	double m_move;
	float m_speed;
	bool m_sprint;
	float m_yaw;
	float m_pitch;
	float m_stepLen;
	float m_stepHeight;
};

