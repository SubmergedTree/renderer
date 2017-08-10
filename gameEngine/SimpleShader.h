#pragma once

#include "ShaderBase.h"
#include <string>
#include <glm\glm.hpp>

namespace gE
{

	class SimpleShader : public ShaderBase
	{
	public:
		SimpleShader(std::string vertexPath, std::string fragmentPath);
		~SimpleShader();

		void bindAttributes();

		void loadProjection(glm::mat4 projectionMatrix);
		void loadView(glm::mat4 viewMatrix);
		void loadModel(glm::mat4 modelMatrix);
		void loadTextures();

		//Lightning
		void setLightProperties(glm::vec3& ambientColor, glm::vec3& diffuseColor, glm::vec3& specularColor);
	//	void setMaterialProperties(glm::vec3&  ambient, glm::vec3&  diffuse, glm::vec3&  specular, GLfloat shininess);
		void setShininess(GLfloat shininess);

		void setLightPosition(glm::vec3 lightPos);
		void setCameraPosition(glm::vec3 camPos);

	private:
		GLint projectionLocation;
		GLint viewLocation;
		GLint modelLocation;
		GLint diffuseTex, specularTex;
		GLint ambientColorLoc, diffuseColorLoc, specularColorLoc;
		GLint shininessLoc;
		GLint lightPosLoc, camPosLoc;
	};


}