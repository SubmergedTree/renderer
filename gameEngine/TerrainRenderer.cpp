#include "TerrainRenderer.h"

namespace gE
{

	TerrainRenderer::TerrainRenderer(TerrainShader * terrainShader, GLfloat fov, GLfloat screenWidth, GLfloat screenHeight) :
		fov(fov), screenWidth(screenWidth), screenHeight(screenHeight)
	{
		this->terrainShader = terrainShader;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}


	TerrainRenderer::~TerrainRenderer()
	{
	}

	void TerrainRenderer::render(TerrainMesh & tMG, glm::mat4 & viewMatrix)
	{
		glBindVertexArray(tMG.model->getVao());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);


		terrainShader->startShaderProgram();

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tMG.diffuseBackground.getTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tMG.specularBackground.getTextureID());

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, tMG.diffuseR.getTextureID());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, tMG.specularR.getTextureID());

		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, tMG.diffuseG.getTextureID());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, tMG.specularG.getTextureID());

		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, tMG.diffuseB.getTextureID());
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, tMG.specularB.getTextureID());

		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, tMG.blendMap.getTextureID());
	

		TerrainRenderer::loadShaderUniforms(viewMatrix,tMG.xPosition, tMG.zPosition);

		glDrawElements(GL_TRIANGLES, tMG.model->getVertexNumber(), GL_UNSIGNED_INT, 0);

		terrainShader->stopShaderProgram();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);
	}

	void TerrainRenderer::loadShaderUniforms(glm::mat4 & viewMatrix, GLfloat xpos, GLfloat zpos)
	{
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 1000.0f); // last number is rendering distance
		terrainShader->loadProjection(projection);

		terrainShader->loadView(viewMatrix);

		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(xpos, 0.0f, zpos));
		terrainShader->loadModel(modelMatrix);
	}

}