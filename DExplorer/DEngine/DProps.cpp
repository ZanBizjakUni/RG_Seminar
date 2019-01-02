#include "DProps.h"

namespace DEngine {
/*
	DProps::DProps()
	{
	}

	DProps::DProps(int w, int h) {
		m_height = h;
		m_width = w;
	}


	DProps::~DProps()
	{
	}
	*/

	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }
	void setDelta() { deltaTime = endTime - beginTime; }
	int height = 0;
	int width = 0;
	float fov = 45.0f;
	float sensitivity = 0.05f;
	double beginTime = 0;
	double endTime = 0;
	double deltaTime = 0;
	float gravity = 0.1f;

}