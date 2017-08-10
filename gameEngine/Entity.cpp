#include "Entity.h"

namespace gE
{

	Entity::Entity(TexturedModel * texModel, glm::vec3& position, GLfloat angle, glm::vec3& rotateAround, glm::vec3& scale) : 
		texModel(texModel), position(position), angle(angle), rotateAround(rotateAround), scale(scale)
	{}

	Entity::~Entity()
	{
		delete texModel;
		texModel = nullptr;
	}

	glm::vec3 Entity::getPosition()
	{
		return position;
	}

	glm::vec3 Entity::getRotateAround()
	{
		return rotateAround;
	}

	glm::vec3 Entity::getScale()
	{
		return scale;
	}

	GLfloat Entity::getAngle()
	{
		return angle;
	}

	TexturedModel * Entity::getTexturedModel()
	{
		return texModel;
	}

	void Entity::setPosition(glm::vec3& position)
	{
		this->position = position;
	}

	void Entity::setAngle(GLfloat angle)
	{
		this->angle = angle;
	}

	void Entity::setRotateAround(glm::vec3& rotateAround)
	{
		this->rotateAround = rotateAround;
	}

	void Entity::setScale(glm::vec3& scale)
	{
		this->scale = scale;
	}
}