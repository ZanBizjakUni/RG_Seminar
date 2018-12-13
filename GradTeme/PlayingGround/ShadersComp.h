#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
namespace PlayingGround {

	class ShadersComp
	{
	public:
		ShadersComp();
		~ShadersComp();
		//funkcija za compilanje shaderjev
		void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);
		void linkShaders();
		void use();
		void unuse();
		GLint returnColorIndex();
		const GLuint returnProgramID() { return m_programID; }
		//	void unuse();
	private:
		void compileShader(GLuint id, std::string shaderPath);
		GLuint m_vertexShaderID;
		GLuint m_fragmentShaderID;
		GLuint m_programID;
	};

} //namespace