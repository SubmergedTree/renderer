#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gE
{
	class Camera
	{
	public:
		Camera() {}

		virtual glm::mat4 getViewMatrix() = 0;
		virtual void setDeltaTime(float deltaTime) = 0;
		virtual glm::vec3 getCameraPosition() = 0;
	};

}