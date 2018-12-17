#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>

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
		BO getBinder(std::string name) { return m_binders[name]; }
	private:
		std::unordered_map<std::string, BO> m_binders;
	};

} //namespace

