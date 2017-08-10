#pragma once

#include "TexturedModel.h"
#include <glm\glm.hpp>


namespace gE
{

	class Entity
	{
	public:
		Entity(TexturedModel * texModel, glm::vec3& position, GLfloat angle = 0, glm::vec3& rotateAround = glm::vec3(1,1,1), glm::vec3& scale = glm::vec3(1,1,1));
		~Entity();

		glm::vec3 getPosition();
		glm::vec3 getRotateAround();
		glm::vec3 getScale();
		GLfloat getAngle();
		TexturedModel* getTexturedModel();

		void setPosition(glm::vec3& position);
		void setAngle(GLfloat angle);
		void setRotateAround(glm::vec3& rotateAround);
		void setScale(glm::vec3& scale);

	private:

		TexturedModel * texModel;
		glm::vec3 position;
		GLfloat angle;
		glm::vec3 rotateAround;
		glm::vec3 scale;
	};


}