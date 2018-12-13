#pragma once
#include <string>
#include "GLTexture.h"
namespace PlayingGround {

	class ImageLoader
	{
	public:
		ImageLoader();
		~ImageLoader();
		void loadImage(std::string texturePath);
		GLuint returnTexID() { return texture.id; }
	private:
		GLTexture texture;

	};

}