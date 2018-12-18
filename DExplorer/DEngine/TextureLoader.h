#pragma once


#include "stb_image.h"

#include <glad/glad.h>

#include "ErrorMsg.h"
#include <string>

namespace DEngine {

	class TextureLoader {
	public:
		TextureLoader();
		~TextureLoader();

		void bindTexture(std::string imgPath);

		unsigned int getId() { return m_texture; }
	private:
		int m_width, m_height, m_nrChannels;
		unsigned int m_texture;
	};

} //namespace

