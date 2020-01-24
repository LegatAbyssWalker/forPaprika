#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat sensitivity)
	: position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(movementSpeed), mouseSensitivity(sensitivity) {


	front = glm::vec3(0.f, 0.f, -1.f);
	updateCameraVectors();
}

void Camera::processKeyboard(sf::Keyboard::Key& key, bool isPressed, GLfloat deltaTime) {
	GLfloat velocity = movementSpeed * deltaTime;
	
	// WASD
	if (key == sf::Keyboard::W) { position += front * velocity; }
	if (key == sf::Keyboard::A) { position -= right * velocity; }
	if (key == sf::Keyboard::S) { position -= front * velocity; }
	if (key == sf::Keyboard::D) { position += right * velocity; }

	// SHIFT/SPACE
	if (key == sf::Keyboard::LShift) { position -= up * velocity; }
	if (key == sf::Keyboard::Space)  { position += up * velocity; }
}

void Camera::processMouseMovement(GLWindow& window) {
	if (window.getWindow().hasFocus() && sf::Mouse::getPosition(window.getWindow()).y >= 0) {
		auto change = sf::Mouse::getPosition(window.getWindow()) - lastMousePosition;

		change.x *= mouseSensitivity;
		change.y *= mouseSensitivity;

		yaw += change.x;
		pitch += change.y;

		// Make sure that when the pitch is out of bounds, the screen does not flip
		if (pitch > 89.f) {
			pitch = 89.f;
		}
		if (pitch < -89.f) {
			pitch = -89.f;
		}

		// Update front, right, and up vectors when updating euler angles
		updateCameraVectors();

		sf::Mouse::setPosition(sf::Vector2<int>((int)window.getWindow().getSize().x / 2, (int)window.getWindow().getSize().y / 2 ), window.getWindow());
		
		lastMousePosition = sf::Mouse::getPosition(window.getWindow());
	}
}

void Camera::updateCameraVectors() {
	glm::vec3 functionFront;

	functionFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	functionFront.y = sin(glm::radians(-pitch)); // Should be `pitch instead of `-pitch` but it works with `-pitch` so why not. 
	functionFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front   = glm::normalize(functionFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}