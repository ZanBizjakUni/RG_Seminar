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

	class Binder {
	public:
		Binder();
		~Binder();
		void setBinder(std::string binderName, std::vector<float> verts, std::vector<unsigned int> ind);
		void setTextureBinder(std::string imgLoc);

		unsigned int getTextureBinder(std::string name) { return m_textureBinder[name].getId(); }
		BO getBinder(std::string name) { return m_binders[name]; }
	private:
		std::unordered_map<std::string, BO> m_binders;
		std::unordered_map<std::string, TextureLoader> m_textureBinder;
	};

} //namespace

