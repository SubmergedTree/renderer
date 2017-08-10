#pragma once

#include "Input.h"
#include <glm\glm.hpp>



namespace gE
{

	class MousePicker
	{
	public:
		MousePicker(glm::mat4& projectionMatrix, int windowWidth, int windowHeight, glm::mat4& viewMatrix,glm::vec3& cameraPosition);
		~MousePicker();

		void update(glm::mat4& viewMatrix, glm::vec3& cameraPosition);

		glm::vec3 getRay();
		glm::vec3 getOrigin();

	private:
		glm::vec2 toNormalizedDeviceCoordinates(float mouseX, float mouseY);
		glm::vec4 toEyeCoordinates(glm::vec4& clipCoords);
		glm::vec3 toWorldCoordinates(glm::vec4& eyeCoords);

		glm::vec3 calculateMouseRay();

		glm::mat4 projectionMatrix;
		glm::vec3 ray;

		Input input;

		int windowWidth;
		int windowHeight;
		glm::mat4 viewMatrix;
		glm::vec3 rayOrigin;
	};

}