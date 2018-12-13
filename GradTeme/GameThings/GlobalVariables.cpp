#pragma once
#include "GlobalVariables.h"
namespace GameThings {
	float rotAnim = 0.0005f;
	int height = 600;
	int width = 800;
	float cameraSpeed = 5.0f;
	GLfloat deltaTime = 0;
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float sensitivity = 0.05f;
	float pitch = 0.0f;
	float yaw = -90.0f;
	float prevYaw = yaw;
	glm::mat4 projection;
	glm::mat4 view;
	GLuint chID;
	unsigned int counter = 0;
} //namespace