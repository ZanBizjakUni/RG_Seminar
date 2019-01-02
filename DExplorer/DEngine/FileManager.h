#pragma once

#include <fstream>
#include <glm/glm.hpp>

namespace DEngine {

	class FileManager {
	public:
		FileManager();
		~FileManager();
		static void write2f(std::ofstream& file, glm::vec2 v);
		static void write3f(std::ofstream& file, glm::vec3 v);
		static void write4f(std::ofstream& file, glm::vec4 v);
		static void writeM4(std::ofstream& file, glm::mat4 v);
		static void writeM3(std::ofstream& file, glm::mat3 v);

	};

}
