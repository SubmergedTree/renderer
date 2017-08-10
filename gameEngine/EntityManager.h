#pragma once

#include "Entity.h"

#include <vector>
#include "Renderer.h"
#include<glm\glm.hpp>

namespace gE
{

	class EntityManager
	{
	public:
		EntityManager(Renderer const& renderer);
		~EntityManager();

		void addEntity(Entity& entity);
		
		void renderEntities(glm::mat4& viewMatrix);

	private:
		std::vector<Entity*> entities;
		Renderer renderer;
	};

}