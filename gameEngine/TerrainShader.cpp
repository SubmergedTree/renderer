#include "TerrainShader.h"

namespace gE
{

	TerrainShader::TerrainShader(std::string vertexPath, std::string fragmentPath) : ShaderBase(vertexPath, fragmentPath)
	{
		bindAttributes();

		createProgram();
		projectionLocation = getUniformLocation("projection");
		viewLocation = getUniformLocation("view");
		modelLocation = getUniformLocation("model");

		ambientColorLoc = getUniformLocation("light.ambient");
		diffuseColorLoc = getUniformLocation("light.diffuse");
		specularColorLoc = getUniformLocation("light.specular");
		shininessLoc = getUniformLocation("material.shininess");
		lightPosLoc = getUniformLocation("light.position");
		camPosLoc = getUniformLocation("viewPos");


		diffuseTexR = getUniformLocation("material.diffuseR");
		specularTexR = getUniformLocation("material.specularR");

		diffuseTexG = getUniformLocation("material.diffuseG");
		specularTexG = getUniformLocation("material.specularG");

		diffuseTexB = getUniformLocation("material.diffuseB");
		specularTexB = getUniformLocation("material.specularB");

		diffuseBackground = getUniformLocation("material.diffuseBackground");
		specularBackground = getUniformLocation("material.specularbackground");

		blendMap = getUniformLocation("blendMap");

	}


	TerrainShader::~TerrainShader()
	{
	}

	void TerrainShader::bindAttributes()
	{
		bindAttribute(0, "aPos");
		bindAttribute(1, "aTexCoord");
		bindAttribute(2, "aNormal");
	}

	void TerrainShader::loadProjection(glm::mat4 projectionMatrix)
	{
		loadMatrix(projectionLocation, projectionMatrix);
	}

	void TerrainShader::loadView(glm::mat4 viewMatrix)
	{
		loadMatrix(viewLocation, viewMatrix);
	}

	void TerrainShader::loadModel(glm::mat4 modelMatrix)
	{
		loadMatrix(modelLocation, modelMatrix);
	}

	void TerrainShader::loadTextures()
	{
		loadInt(diffuseBackground, 0);
		loadInt(specularBackground, 1);
		loadInt(diffuseTexR, 2);
		loadInt(specularTexR, 3);
		loadInt(diffuseTexG, 4);
		loadInt(specularTexG, 5);
		loadInt(diffuseTexB, 6);
		loadInt(specularTexB, 7);
		loadInt(blendMap, 8);
	}

	void TerrainShader::setLightProperties(glm::vec3 & ambientColor, glm::vec3 & diffuseColor, glm::vec3 & specularColor)
	{
		loadVector3(ambientColorLoc, ambientColor);
		loadVector3(diffuseColorLoc, diffuseColor);
		loadVector3(specularColorLoc, specularColor);
	}

	void TerrainShader::setShininess(GLfloat shininess)
	{
		loadFloat(shininessLoc, shininess);
	}


	void TerrainShader::setLightPosition(glm::vec3 lightPos)
	{
		loadVector3(lightPosLoc, lightPos);
	}

	void TerrainShader::setCameraPosition(glm::vec3 camPos)
	{
		loadVector3(camPosLoc, camPos);
	}

}