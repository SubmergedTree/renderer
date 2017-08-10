#include "MousePicker.h"

using namespace glm;

#include <iostream>

namespace gE
{

	MousePicker::MousePicker(glm::mat4& projectionMatrix, int windowWidth, int windowHeigh, glm::mat4& viewMatrix, glm::vec3& cameraPosition) :
		projectionMatrix(projectionMatrix) ,windowWidth(windowWidth), windowHeight(windowHeight), viewMatrix(viewMatrix), rayOrigin(cameraPosition)
	{
		ray = calculateMouseRay();
	}

	MousePicker::~MousePicker()
	{}

	void MousePicker::update(glm::mat4& viewMatrix,glm::vec3& cameraPosition)
	{
		this->viewMatrix = viewMatrix;
		this->rayOrigin = cameraPosition;

		ray = calculateMouseRay();
	}

	glm::vec3 MousePicker::getRay()
	{
		return ray;
	}

	glm::vec3 MousePicker::getOrigin()
	{
		return rayOrigin;
	}

	glm::vec2 MousePicker::toNormalizedDeviceCoordinates(float mouseX, float mouseY)
	{
		float x = (2.0f * mouseX) / windowWidth - 1.f;
		float y = 1.0f - (2.0f * mouseY) / windowHeight;
		
		return glm::vec2(x,y);
	}

	glm::vec4 MousePicker::toEyeCoordinates(glm::vec4& clipCoords)
	{
		vec4 eyeCoords = inverse(projectionMatrix) * clipCoords;
		return glm::vec4(eyeCoords.x, eyeCoords.y,-1.0,0.0);
	}

	glm::vec3 MousePicker::toWorldCoordinates(glm::vec4& eyeCoords)
	{
		vec4 worldCoords = (inverse(viewMatrix) * eyeCoords);
		return normalize(vec3(worldCoords.x,worldCoords.y,worldCoords.z));
	}
	glm::vec3 MousePicker::calculateMouseRay()
	{
		float mouseX = input.getMouseX();
		float mouseY = input.getMouseY();

		vec2 normalizedCoords = toNormalizedDeviceCoordinates(mouseX, mouseY);
		vec4 clipCoords = vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
		vec4 eyeCoords = toEyeCoordinates(clipCoords);

		return toWorldCoordinates(eyeCoords);
	}
}