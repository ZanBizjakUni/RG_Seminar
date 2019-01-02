#include "FileManager.h"

namespace DEngine {

	FileManager::FileManager() {}


	FileManager::~FileManager() {}

	void FileManager::write2f(std::ofstream & file, glm::vec2 v) {
		float tmp;
		tmp = v.x;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.y;
		file.write((char*)&tmp, sizeof(float));
	
	}

	void FileManager::write3f(std::ofstream & file, glm::vec3 v) {
		float tmp;
		tmp = v.x;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.y;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.z;
		file.write((char*)&tmp, sizeof(float));

	}

	void FileManager::write4f(std::ofstream & file, glm::vec4 v) {
		float tmp;
		tmp = v.x;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.y;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.z;
		file.write((char*)&tmp, sizeof(float));
		tmp = v.w;
		file.write((char*)&tmp, sizeof(float));


	}

	void FileManager::writeM4(std::ofstream & file, glm::mat4 v) {
		float tmp;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp = v[i][j];
				file.write((char*)&tmp, sizeof(float));
			}
		}
	}

	void FileManager::writeM3(std::ofstream & file, glm::mat3 v) {
		float tmp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				tmp = v[i][j];
				file.write((char*)&tmp, sizeof(float));
			}
		}
	}
}