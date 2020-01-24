#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"
#include "Variables.h"
#include "Program.h"
#include "Mesh.h"
#include "FileLocations.h"

#include <iostream>
#include <memory>

class Player {
	public:
		Player(GLWindow& window, glm::vec3 position, glm::mat4 projection);

		void keyboardUpdate(sf::Keyboard::Key& key, bool isPressed, GLfloat deltaTime);
		void mouseUpdate();
		void update(GLfloat deltaTime);
		void render();

		glm::mat4 getViewMatrix() { return camera.calculateViewMatrix(); }
		const glm::vec3 getPosition() { return camera.getPosition(); }

	private:
		GLWindow& window;

		bool w, a, s, d, space, lShift;

		GLfloat deltaTime;

		Camera camera;
		GLfloat lastX = window.getWindow().getSize().x / 2.f;
		GLfloat lastY = window.getWindow().getSize().y / 2.f;
		bool firstMouse = true;

		Mesh mesh;
		std::shared_ptr<Program> program;
};

#endif