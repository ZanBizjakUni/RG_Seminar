#include "ImageLoader.h"
#include <SOIL\SOIL.h>
#include <GL\glew.h>
#include "GLTexture.h"
#include <iostream>

namespace PlayingGround {

	ImageLoader::ImageLoader()
	{
	}


	ImageLoader::~ImageLoader()
	{
	}

	void ImageLoader::loadImage(std::string texturePath) {
		//za vsako koordinato nastavimo nastavitve, kako se bo slika izrisala. s,t,r so ekvivalent x,y,z
		//s in t sintaksa je enaka kot u in v

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		unsigned char* image = SOIL_load_image(texturePath.c_str(), &texture.width, &texture.height, 0, SOIL_LOAD_RGBA);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		std::cout << texturePath << " " << texture.id << "\n";
	}

} //namespace