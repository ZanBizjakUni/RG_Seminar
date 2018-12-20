#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>

#include "TextureLoader.h"

namespace DEngine {
	struct BO {
		unsigned int VBO, VAO, EBO;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
	};
	///class Binder
	/*
	* This class is in charge of storing the binded textures and vertices
	*/
	class Binder {
	public:
		Binder();
		~Binder();
		///void setBinder(std::string binderName, std::vector<float> verts, std::vector<unsigned int> ind)
		/*
		* sets the binder for vertices inputed as an argument.
		* binderName is the key the binder will be stored in (in an unordered map)
		* verts is the vector of vertices that will be bound to the specific VBO
		* ind is the vector of indices that will be obund  to the specific EBO
		* VAO is generated for each new vector
		*/
		void setBinder(std::string binderName, std::vector<float> verts, std::vector<unsigned int> ind = {});

		///void setTextureBinder(std::string imgLoc)
		/*
		* sets the binder for the texture (image) inputed as the argument
		* imgLoc is the path to the image file that will be bound
		*/
		void setTextureBinder(std::string imgLoc);

		///unsigned int getTextureBinder(std::string name)
		/*
		* returns the id of the bound texture
		*/
		unsigned int getTextureBinder(std::string name) { return m_textureBinder[name].getId(); }

		/*
		* returns the id of the bound VAO
		*/
		BO getBinder(std::string name) { return m_binders[name]; }
	private:
		std::unordered_map<std::string, BO> m_binders;
		std::unordered_map<std::string, TextureLoader> m_textureBinder;
	};

} //namespace

