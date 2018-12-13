#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Vertex.h"
#include "ImageLoader.h"
#include "GLTexture.h"
#include <string>
#include <vector>

namespace PlayingGround {

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();
		void init(std::string texName, std::vector<float> vertecies, bool);
		void draw(GLuint pID, std::string sampler);

	private:
		void createVertexArray(std::vector<float> vertecies);
		bool m_hasTexture;
		// vertex buffer object
		GLuint m_VBO;
		// vertex array object
		// uporablja se za shranjevanje VBO
		GLuint m_VAO;
		GLuint m_EBO;
		GLsizei m_numOfVerts;

		std::string m_textureName;
		ImageLoader m_img1;
		
		GLTexture texture;
	};

} //namespace