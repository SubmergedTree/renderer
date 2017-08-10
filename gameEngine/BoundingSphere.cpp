#include "BoundingSphere.h"

#include <glm/gtx/transform.hpp>
#include <iostream>

namespace gE
{

	BoundingSphere::BoundingSphere(glm::vec3& centroid, double radius, glm::vec3& scale)  : centroid(centroid), radius(radius)
	{
		position = glm::vec3(0, 0, 0);
	}


	BoundingSphere::~BoundingSphere()
	{
	}

	void BoundingSphere::update(glm::vec3& position, glm::vec3& scale)
	{
		glm::vec3 originalCentroid = centroid - this->position;
		centroid = originalCentroid + position;
		this->position = position;
	//	centroid = position;
	}

	void BoundingSphere::collisionBS(BoundingSphere const& bs)
	{
	//	std::cout << this->centroid.x << " " << this->centroid.y << " " << this->centroid.z << std::endl;
	//	std::cout << this->radius << " " << bs.radius << std::endl;
		double distanceCentroid = glm::length(bs.centroid - this->centroid);
		double distanceRadius = bs.radius + this->radius;

		if (distanceCentroid <= distanceRadius)
		{
			std::cout << "collision" << std::endl;
		}
	}

	bool BoundingSphere::collisionRay(glm::vec3& ray, glm::vec3& origin)
	{
		glm::vec3 first = glm::cross(ray, (centroid - origin));

		float second = glm::length(first);
		float thirt = glm::length(centroid);

		float d = second / thirt;

		if (d >= radius)
		{
			return false;
		}


		return true;
	}

}