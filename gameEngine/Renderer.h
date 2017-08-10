#pragma once

#include "SimpleShader.h"
#include "TexturedModel.h"

#include <glm\glm.hpp>

namespace gE
{
	class Renderer
	{
	public:
		Renderer(SimpleShader * simpleShader,GLfloat fov,GLfloat screenWidth,GLfloat screenHeight);
		~Renderer();

		void render(TexturedModel * texModel,
			glm::mat4& viewMatrix,
			glm::vec3& position,
			GLfloat angle,
			glm::vec3& rotateAround,
			glm::vec3& scale);

	private:
		//void enableCulling();
		//void disableCulling();

		void loadShaderUniforms(glm::mat4& viewMatrix,
			glm::vec3& position,
			GLfloat angle,
			glm::vec3& rotateAround,
			glm::vec3& scale);

		SimpleShader* simpleShader;
		GLfloat screenWidth, screenHeight;
		GLfloat fov;
		glm::mat4 viewMatrix;
		glm::vec3 position;
		GLfloat angle;
		glm::vec3 rotateAround;
	};

}

