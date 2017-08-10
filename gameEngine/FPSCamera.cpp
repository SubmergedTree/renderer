#include "FPSCamera.h"


namespace gE
{



	FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
		Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM), deltaTime(0)
	{

		//keyTrack = registerCallbackOnKeyPressed(std::bind(&FPSCamera::processKeyboard,this, KEY_CALLBACK_ARGS));
		mouseTrack = registerCallbackOnMouseMove(std::bind(&FPSCamera::processMouse, this, MOUSE_CALLBACK_ARGS));
		//scrollTrack = registerCallbackOnScroll(std::bind(&FPSCamera::processScroll, this, SCROLL_CALLBACK_ARGS));

		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;


		input = new Input();

		updateCamera();
	}


	FPSCamera::~FPSCamera()
	{
		//TODO: delete callback bindings
	}

	glm::mat4 FPSCamera::getViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	void FPSCamera::setDeltaTime(float deltaTime)
	{
		this->deltaTime = deltaTime;

		processKeyboard(1);
		//processMouse(input->getMouseX(), input->getMouseY());
	}

	void FPSCamera::processKeyboard(int key)
	{
		float velocity = MovementSpeed * deltaTime;

		/*if (key == GLFW_KEY_W)
			Position += Front * velocity;
		if (key == GLFW_KEY_S)
			Position -= Front * velocity;
		if (key == GLFW_KEY_A)
			Position -= Right * velocity;
		if (key == GLFW_KEY_D)
			Position += Right * velocity;*/
		

		if (input->isKeyPressed(GLFW_KEY_W))
			Position += Front * velocity;
		if (input->isKeyPressed(GLFW_KEY_S))
			Position -= Front * velocity;
		if (input->isKeyPressed(GLFW_KEY_A))
			Position -= Right * velocity;
		if (input->isKeyPressed(GLFW_KEY_D))
			Position += Right * velocity;

		updateCamera();
	}


	float lastX = 1280 / 2.0f;
	float lastY = 720 / 2.0f;
	bool firstMouse = true;

	void FPSCamera::processMouse(double x, double y)
	{
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}

		float xoffset = x - lastX;
		float yoffset = lastY - y; // reversed since y-coordinates go from bottom to top

		lastX = x;
		lastY = y;


		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
	//	if (constrainPitch)
	//	{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
	//	}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCamera();
	}

	void FPSCamera::processScroll(double xOffset, double yOffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yOffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;

		updateCamera();
	}

	glm::vec3 FPSCamera::getCameraPosition()
	{
		return Position;
	}

	void FPSCamera::updateCamera()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}

}