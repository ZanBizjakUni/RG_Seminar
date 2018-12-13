#include <SOIL\SOIL.h>

#include "SpriteBatch.h"
#include <iostream>

namespace PlayingGround {


	SpriteBatch::SpriteBatch() :m_VAO(0), m_VBO(0), m_EBO(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}


	void SpriteBatch::init(std::string texName, std::vector<float> vertecies, bool tex) {
		m_hasTexture = tex;
		m_textureName = texName;
		createVertexArray(vertecies);
		if (m_hasTexture) {
			glActiveTexture(GL_TEXTURE0);
			m_img1.loadImage(m_textureName);
			texture.id = m_img1.returnTexID();


			glGenTextures(1, &texture.id);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture.id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			unsigned char* image = SOIL_load_image(texName.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGBA);


			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

		}
	//	SOIL_free_image_data(image);
	//	glBindTexture(GL_TEXTURE_2D, 0);

		//glGenTextures(1, &texture1.id);
	/*	glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1.id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char* image1 = SOIL_load_image("awsomeface.jpg", &texture1.width, &texture1.height, 0, SOIL_LOAD_RGB);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture1.width, texture1.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image1);
		glBindTexture(GL_TEXTURE_2D, 0);*/

	}

	void SpriteBatch::createVertexArray(std::vector<float> vertecies) {
		
		if (m_hasTexture) {
			m_numOfVerts = vertecies.size() / 5;
		}
		else {
			m_numOfVerts = vertecies.size() / 6;
		}
		glGenVertexArrays(1, &m_VAO);
	//	glGenBuffers(1, &m_EBO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		float* tmp = &vertecies[0];
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tmp) * vertecies.size(), tmp, GL_STATIC_DRAW);

	/*	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);*/

		if (m_hasTexture) {
			//position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) *5 , (GLvoid*)0);
			glEnableVertexAttribArray(0);									 
																			 
		/*	//color															 
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) *5 , (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);*/									  
																			  
																			  
		/*	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) *5 , (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);	*/								  
			//uv															  
																			  
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) *5 , (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
		else {
			//position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)0);
			glEnableVertexAttribArray(0);

			/*	//color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);*/


			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		}
		/*	glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			//position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,position));


			//color
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,color));


			//uv
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex,uv));
			*/

		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}

	void SpriteBatch::draw(GLuint pID,std::string sampler) {
		if (m_hasTexture) {
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glUniform1i(glGetUniformLocation(pID, sampler.c_str()), 0);
		}
		
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, m_numOfVerts);
		glBindVertexArray(0);
	}

} //namespace