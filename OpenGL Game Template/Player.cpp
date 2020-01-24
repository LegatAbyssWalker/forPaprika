#include "Player.h"

Player::Player(GLWindow& window, glm::vec3 position, glm::mat4 projection)
	: window(window) {
	// Camera
	camera = Camera(position, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 10.f, 0.3f);
}

void Player::keyboardUpdate(sf::Keyboard::Key& key, bool isPressed, GLfloat deltaTime) {
	// Camera event updates
	camera.processKeyboard(key, isPressed, deltaTime);
}

void Player::mouseUpdate() {
	camera.processMouseMovement(window);
}

void Player::update(GLfloat deltaTime) {
	this->deltaTime = deltaTime;
	mouseUpdate();
}

void Player::render() {

	// ? 
}
