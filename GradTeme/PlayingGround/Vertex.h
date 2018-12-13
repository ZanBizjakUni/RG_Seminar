#pragma once

#include <GL\glew.h>

namespace PlayingGround{

	struct ColorRGBA8 {
		ColorRGBA8() : r(0), g(0), b(0), a(0) {}
		ColorRGBA8(GLfloat R, GLfloat G, GLfloat B, GLfloat A) : r(R), g(G), b(B), a(A) {}
		GLfloat r;
		GLfloat g;
		GLfloat b;
		GLfloat a;
	};

	struct UV {
		GLfloat u;
		GLfloat v;
	};


	struct Vertex {
		glm::vec3 position;
		UV uv;
		glm::vec3 normal;
		void setPosition(GLfloat x, GLfloat y, GLfloat z) {
			position.x = x;
			position.y = y;
			position.z = z;
		}


		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
		void setNormal(GLfloat x, GLfloat y, GLfloat z) {
			normal.x = x;
			normal.y = y;
			normal.z = z;
		}
	};

}