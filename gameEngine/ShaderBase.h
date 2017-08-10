#pragma once

#include <GL\glew.h>

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace gE
{

	class ShaderBase
	{
	public:
		ShaderBase(std::string vertex, std::string fragment);
		~ShaderBase();

		void startShaderProgram();
		void stopShaderProgram();

	protected:
		void loadFloat(GLint location,GLfloat value);
		void loadInt(GLint location, GLint value);
		void loadBool(GLint location, bool value);
		void loadVector4(GLint location,glm::vec4 vector4);
		void loadVector2(GLint location,glm::vec2 vector2 );
		void loadVector3(GLint location, glm::vec3 vector3);
		void loadMatrix(GLint location, glm::mat4x4 matrix);

		GLint getUniformLocation(std::string uniformName);

		void bindAttribute(GLint attribute, std::string attributeName);

		void createProgram();

	private:

		void compileShader(std::string shader, GLint type);
		void validateProgram(GLuint shader, std::string type);

		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

	};

}