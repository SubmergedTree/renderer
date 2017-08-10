#include "ShaderBase.h"

#include "FileLoader.h"


namespace gE
{

	ShaderBase::ShaderBase(std::string vertex, std::string fragment)
	{
		std::string vertexRaw =  loadFromFile(vertex);
		std::string fragmentRaw = loadFromFile(fragment);

		compileShader(vertexRaw, GL_VERTEX_SHADER);
		compileShader(fragmentRaw, GL_FRAGMENT_SHADER);

		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);

	}


	ShaderBase::~ShaderBase()
	{
		glDeleteProgram(programID);
	}

	void ShaderBase::startShaderProgram()
	{
		glUseProgram(programID);
	}

	void ShaderBase::stopShaderProgram()
	{
		glUseProgram(0);
	}

	void ShaderBase::bindAttribute(GLint attribute, std::string attributeName)
	{
		glBindAttribLocation(programID, attribute, attributeName.c_str());
	}

	void ShaderBase::loadFloat(GLint location, GLfloat value)
	{
		glUniform1f(location, value);
	}

	void ShaderBase::loadInt(GLint location, GLint value)
	{
		glUniform1i(location, value);
	}

	void ShaderBase::loadBool(GLint location, bool value)
	{
		//TODO
	}

	void ShaderBase::loadVector4(GLint location, glm::vec4 vector4)
	{
		glUniform4f(location,vector4.x,vector4.y,vector4.z,vector4.w);
	}

	void ShaderBase::loadVector2(GLint location, glm::vec2 vector2)
	{
		glUniform2f(location, vector2.x, vector2.y);
	}

	void ShaderBase::loadVector3(GLint location, glm::vec3 vector3)
	{
		glUniform3f(location, vector3.x, vector3.y, vector3.z);
	}

	void ShaderBase::loadMatrix(GLint location, glm::mat4x4 matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	GLint ShaderBase::getUniformLocation(std::string uniformName)
	{
		return glGetUniformLocation(programID,uniformName.c_str());
	}

	void ShaderBase::compileShader(std::string shader, GLint type)
	{
		GLuint shaderID = glCreateShader(type);
		
		const char* src_cstr = shader.c_str();
		glShaderSource(shaderID,1, &src_cstr, NULL);
		glCompileShader(shaderID);



		if (type == GL_VERTEX_SHADER)
		{
			vertexShaderID = shaderID;
			validateProgram(programID, "VERTEX");

		}
		else
		{
			fragmentShaderID = shaderID;
			validateProgram(programID, "FRAGMENT");

		}
	}

	void ShaderBase::createProgram()
	{
		//	programID = glCreateProgram();
		//	glAttachShader(programID,vertexShaderID);
		//	glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		validateProgram(programID, "PROGRAM");
		glValidateProgram(programID);
		//	glDeleteShader(vertexShaderID);
		//	glDeleteShader(fragmentShaderID);
	}

	void ShaderBase::validateProgram(GLuint shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}


}