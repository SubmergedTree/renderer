#include "SimpleShader.h"



namespace gE
{

	SimpleShader::SimpleShader(std::string vertexPath, std::string fragmentPath) : ShaderBase(vertexPath, fragmentPath)
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


		diffuseTex = getUniformLocation("material.diffuse");
		specularTex = getUniformLocation("material.specular");
	}


	SimpleShader::~SimpleShader()
	{
	}

	void SimpleShader::bindAttributes()
	{
		bindAttribute(0, "aPos");
		bindAttribute(1, "aTexCoord");
		bindAttribute(2, "aNormal");
	}

	void SimpleShader::loadProjection(glm::mat4 projectionMatrix)
	{
		loadMatrix(projectionLocation, projectionMatrix);
	}

	void SimpleShader::loadView(glm::mat4 viewMatrix)
	{
		loadMatrix(viewLocation, viewMatrix);
	}

	void SimpleShader::loadModel(glm::mat4 modelMatrix)
	{
		loadMatrix(modelLocation, modelMatrix);
	}

	void SimpleShader::loadTextures()
	{
		loadInt(diffuseTex, 0);
		loadInt(specularTex, 1);
	}

	void SimpleShader::setLightProperties(glm::vec3 & ambientColor, glm::vec3 & diffuseColor, glm::vec3 & specularColor)
	{
		loadVector3(ambientColorLoc, ambientColor);
		loadVector3(diffuseColorLoc, diffuseColor);
		loadVector3(specularColorLoc, specularColor);
	}

	void SimpleShader::setShininess(GLfloat shininess)
	{
		loadFloat(shininessLoc, shininess);
	}


	void SimpleShader::setLightPosition(glm::vec3 lightPos)
	{
		loadVector3(lightPosLoc, lightPos);
	}

	void SimpleShader::setCameraPosition(glm::vec3 camPos)
	{
		loadVector3(camPosLoc, camPos);
	}

}