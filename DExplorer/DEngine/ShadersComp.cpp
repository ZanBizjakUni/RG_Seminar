#include "ShadersComp.h"
#include "ErrorMsg.h"
#include <fstream>
#include <iostream>

namespace DEngine {


	ShadersComp::ShadersComp() : m_vertexShaderID(0), m_fragmentShaderID(0), m_programID(0) {

	}


	ShadersComp::~ShadersComp() {}




	//program za compilanje shaderjev
	void ShadersComp::compileShaders(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath) {

		//ustvarimo programID. ta se bo uporabil
		//pri compilanju/linkanju shaderjev
		m_programID = glCreateProgram();
		//shaderjem damo ID
		//in preverimo ali se je shader uspesno ustvaril
		m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertexShaderID == 0) {
			ErrorMsg::message("Could not create vertex shader ID! \n");
		}

		m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragmentShaderID == 0) {
			ErrorMsg::message("Could not create fragment shader ID!");
		}

		compileShader(m_vertexShaderID, vertexShaderFilePath);
		compileShader(m_fragmentShaderID, fragmentShaderFilePath);
	}

	void ShadersComp::linkShaders() {
		//v program vstavi shaderje
		glAttachShader(m_programID, m_vertexShaderID);
		glAttachShader(m_programID, m_fragmentShaderID);

		glLinkProgram(m_programID);
		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLogLength;
			glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &maxLogLength);

			GLchar* infoLog = (GLchar*)"";
			glGetShaderInfoLog(m_programID, maxLogLength, &maxLogLength, infoLog);
			glDeleteProgram(m_programID);
			glDeleteShader(m_vertexShaderID);
			glDeleteShader(m_fragmentShaderID);

			std::printf("%s\n", infoLog);
			ErrorMsg::message("program failed to link!");

		}

		glDetachShader(m_programID, m_vertexShaderID);
		glDetachShader(m_programID, m_fragmentShaderID);
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);
	}

	void ShadersComp::use() {
		glUseProgram(m_programID);

	}
	void ShadersComp::unuse() {
		glUseProgram(0);
	}

	GLint ShadersComp::returnColorIndex() {
		return glGetUniformLocation(m_programID, "ourColor");
	}

	void ShadersComp::set4f(const std::string & name, glm::vec4 v) {
		glUniform4f(glGetUniformLocation(m_programID, name.c_str()), v.x, v.y, v.z, v.w);
	}

	void ShadersComp::set3f(const std::string & name, glm::vec3 v) {
		
		glUniform3f(glGetUniformLocation(m_programID, name.c_str()), v.x, v.y, v.z);
	}

	void ShadersComp::set3fv(const std::string & name, std::vector<glm::vec3> v) {
		GLfloat* arr = &v[0].x;
		glUniform3fv(m_programID, v.size(), arr);
	}

	void ShadersComp::set2f(const std::string & name, glm::vec2 v) {
		glUniform2f(glGetUniformLocation(m_programID, name.c_str()), v.x, v.y);
	}

	void ShadersComp::set1f(const std::string & name, GLfloat v) {
		glUniform1f(glGetUniformLocation(m_programID, name.c_str()), v);
	}

	void ShadersComp::set1i(const std::string & name, GLint v) {
		glUniform1i(glGetUniformLocation(m_programID, name.c_str()), v);

	}

	void ShadersComp::setMat4fv(const std::string & name, glm::mat4 v) {
		glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
	}

	void ShadersComp::setMat3fv(const std::string & name, glm::mat3 v) {
		glUniformMatrix3fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));

	}



	//funkcija, ki iz datoteke prenese glsl program in ga compila
	void ShadersComp::compileShader(GLuint id, std::string shaderPath) {
		std::ifstream File(shaderPath);
		if (File.fail()) {
			perror(shaderPath.c_str());
				ErrorMsg::message("could not open " + shaderPath);
		}
		std::string sProgram = "";
		std::string line;

		while (std::getline(File, line)) {
			sProgram += line + "\n";
		}
		const char* sContents = sProgram.c_str();
		glShaderSource(id, 1, &sContents, nullptr);
		glCompileShader(id);

		GLint success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE) {
			GLint maxLogLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLogLength);

			GLchar* infoLog = (GLchar*)"";

			glGetShaderInfoLog(id, maxLogLength, &maxLogLength, infoLog);
			
			std::printf("%s\n", infoLog);
			ErrorMsg::message("shader" + shaderPath + " failed to compile");

		}

	}

} //namespace

