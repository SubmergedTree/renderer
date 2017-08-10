#pragma once

#include "ShaderBase.h"
#include <string>
#include <glm\glm.hpp>

namespace gE
{

	class TerrainShader : public ShaderBase
	{
	public:
		TerrainShader(std::string vertexPath, std::string fragmentPath);
		~TerrainShader();

		void bindAttributes();

		void loadProjection(glm::mat4 projectionMatrix);
		void loadView(glm::mat4 viewMatrix);
		void loadModel(glm::mat4 modelMatrix);

		void loadTextures();


		void setLightProperties(glm::vec3& ambientColor, glm::vec3& diffuseColor, glm::vec3& specularColor);
		void setShininess(GLfloat shininess);

		void setLightPosition(glm::vec3 lightPos);
		void setCameraPosition(glm::vec3 camPos);

	private:
		GLint projectionLocation;
		GLint viewLocation;
		GLint modelLocation;

		GLint diffuseTexR, specularTexR, diffuseTexG, specularTexG, diffuseTexB, specularTexB;
		GLint blendMap, diffuseBackground, specularBackground;
		GLint ambientColorLoc, diffuseColorLoc, specularColorLoc;
		GLint shininessLoc;
		GLint lightPosLoc, camPosLoc;

	};

}