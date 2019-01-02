#pragma once

#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DEngine {
	/*class DProps
	{
	public:
		DProps();
		DProps(int w, int h);
		~DProps();
		int getWidth() { return m_width; }
		int getHeight() { return m_height; }
	private:
		int m_height;
		int m_width;

	};
	*/
	extern void setWidth(int w);
	extern void setHeight(int h);
	extern void setDelta();
	extern int height;
	extern int width;
	extern float fov;
	extern float sensitivity;
	extern double beginTime;
	extern double endTime;
	extern double deltaTime;
	extern float gravity;
} //namespace