#include "Renderer.h"

namespace gE
{

	Renderer::Renderer(SimpleShader * simpleShader, GLfloat fov, GLfloat screenWidth, GLfloat screenHeight) :
		fov(fov), screenWidth(screenWidth), screenHeight(screenHeight)
	{
		this->simpleShader = simpleShader;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}


	Renderer::~Renderer()
	{
	}

	void Renderer::loadShaderUniforms(glm::mat4& viewMatrix, glm::vec3& position, GLfloat angle, glm::vec3& rotateAround, glm::vec3& scale)
	{
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		simpleShader->loadProjection(projection);

		simpleShader->loadView(viewMatrix);

		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix, position);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotateAround);
		modelMatrix = glm::scale(modelMatrix,scale);
		simpleShader->loadModel(modelMatrix);
	}

	void Renderer::render(TexturedModel * texModel,
		glm::mat4& viewMatrix,
		glm::vec3& position,
		GLfloat angle,
		glm::vec3& rotateAround,
		glm::vec3& scale)
	{

		glBindVertexArray(texModel->getModel()->getVao());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		simpleShader->startShaderProgram();

		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texModel->getTexture()->getTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texModel->getSpecular()->getTextureID());

		Renderer::loadShaderUniforms(viewMatrix, position, angle, rotateAround,scale);

		glDrawElements(GL_TRIANGLES, texModel->getModel()->getVertexNumber(), GL_UNSIGNED_INT, 0);


		simpleShader->stopShaderProgram();

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindVertexArray(0);

	}


}