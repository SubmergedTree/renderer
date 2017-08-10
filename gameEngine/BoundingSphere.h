#pragma once

#include <glm/glm.hpp>


namespace gE
{
	class BoundingSphere
	{
	public:
		BoundingSphere(glm::vec3& centroid, double radius, glm::vec3& scale = glm::vec3(1,1,1));
		~BoundingSphere();

		void update(glm::vec3& position, glm::vec3& scale = glm::vec3(1,1,1));

		void collisionBS(BoundingSphere const& bs);
		bool collisionRay(glm::vec3& ray, glm::vec3& origin);

	private:
		double radius;
		glm::vec3 centroid;
		glm::vec3 position;
	};

}