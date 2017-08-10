#include "EntityManager.h"
#include <glm\glm.hpp>


namespace gE
{

	EntityManager::EntityManager(Renderer const& renderer) : renderer(renderer)
	{
	}

	EntityManager::~EntityManager()
	{	}

	void EntityManager::addEntity(Entity & entity)
	{
		entities.push_back(&entity);
	}

	void EntityManager::renderEntities(glm::mat4& viewMatrix)
	{
		for (auto it : entities)
		{
			renderer.render(it->getTexturedModel(), viewMatrix, it->getPosition(), it->getAngle(), it->getRotateAround(),it->getScale());
		}
	}

}