#pragma once

#include "Camera.h"
#include "Input.h"

namespace gE
{


	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 10.0f;
	const float SENSITIVTY = 0.1f;
	const float ZOOM = 45.0f;


	class FPSCamera : public Camera
	{
	public:
		FPSCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
		~FPSCamera();

		glm::mat4 getViewMatrix();
		void setDeltaTime(float deltaTime);


		void processKeyboard(int key);
		void processMouse(double x, double y);
		void processScroll(double xOffset, double yOffset);

		glm::vec3 getCameraPosition();

	private:
		// Camera Attributes
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		// Eular Angles
		float Yaw;
		float Pitch;

		// Camera options
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		float deltaTime;

		void updateCamera();


		//callback tracker
		unsigned long mouseTrack, keyTrack, scrollTrack;

		Input * input;
	};


}