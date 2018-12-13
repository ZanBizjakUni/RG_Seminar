#pragma once
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
namespace GameThings {
	extern float rotAnim;
	extern int height;
	extern int width;
	extern float cameraSpeed;
	extern glm::vec3 cameraFront;
	extern glm::vec3 cameraUp;
	extern GLfloat deltaTime;
	extern float sensitivity;
	extern float pitch;
	extern float yaw;
	extern float prevYaw;
	extern glm::mat4 projection;
	extern glm::mat4 view;
	extern GLuint chID;
	extern unsigned int counter;
} //namespace