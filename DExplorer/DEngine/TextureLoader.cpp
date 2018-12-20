#include "TextureLoader.h"

namespace DEngine {

	TextureLoader::TextureLoader() {}


	TextureLoader::~TextureLoader() {}

	void TextureLoader::bindTexture(std::string imgPath) {
		stbi_set_flip_vertically_on_load(true);
		unsigned char* m_data = stbi_load(imgPath.c_str(), &m_width, &m_height, &m_nrChannels, 0);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (!m_data) {
			ErrorMsg::message("Failed to load texutre");

		}

		if (imgPath.find(".jpg") != std::string::npos) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		}
		else if (imgPath.find(".png") != std::string::npos) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(m_data);
	}



} //namespace