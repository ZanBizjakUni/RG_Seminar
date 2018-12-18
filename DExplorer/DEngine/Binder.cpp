#include "Binder.h"

namespace DEngine {
	Binder::Binder() {}


	Binder::~Binder() {}

	void Binder::setBinder(std::string binderName, std::vector<float> verts, std::vector<unsigned int> ind) {
		m_binders[binderName].vertices = verts;
		m_binders[binderName].indices = ind;
		m_binders[binderName].vertices.shrink_to_fit();
		m_binders[binderName].indices.shrink_to_fit();

		glGenVertexArrays(1, &m_binders[binderName].VAO);



		glGenBuffers(1, &m_binders[binderName].VBO);
		glGenBuffers(1, &m_binders[binderName].EBO);

		glBindVertexArray(m_binders[binderName].VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_binders[binderName].VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_binders[binderName].EBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(m_binders[binderName].vertices[0]) * m_binders[binderName].vertices.capacity(), &m_binders[binderName].vertices[0], GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_binders[binderName].indices[0]) * m_binders[binderName].indices.capacity(), &m_binders[binderName].indices[0], GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute ( layout (location = 1) in vert shader)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void Binder::setTextureBinder(std::string imgLoc) {
		m_textureBinder[imgLoc].bindTexture(imgLoc);
	}

} //namespace