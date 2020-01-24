#pragma once

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "GLWindow.h"
#include "FileLocations.h"
#include "Variables.h"
#include "OBJLoader.h"

#include <iostream>
#include <vector>
#include <memory>

class Chest {
	public:
		Chest(GLWindow& window);

		void setPosition(glm::vec3 position);

		void update();
		void render(const glm::mat4 viewMatrix, const glm::mat4 projection);

		glm::vec3 getPosition() const { return glm::vec3(position); }

	private:
		GLWindow& window;
		Mesh mesh;
		std::shared_ptr<Program> program;

		glm::vec3 position;
		glm::vec3 scaleValue = glm::vec3(0.5, 0.5, 0.5);


		OBJLoader objLoader;
};