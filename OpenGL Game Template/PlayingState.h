#pragma once

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <array>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

#include "FileLocations.h"
#include "Variables.h"
#include "GLWindow.h"
#include "Player.h"

#include "Chest.h"

// 
#include "Program.h"
#include "Texture.h"
#include "Mesh.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& window, bool replace = true);

		void keyboardInputs(sf::Keyboard::Key& key, bool isPressed);

		void updateEvents();
		void update();
		void render();

		glm::mat4 getProjectionMatrix() { return glm::perspective(glm::radians(45.f), (GLfloat)window.getWindow().getSize().x / window.getWindow().getSize().y, 0.1f, 100.f); }

	private:
		GLWindow& window;
		sf::Event sfEvent;
		sf::Clock clock;
		GLfloat deltaTime = 0, lastFrame = 0;

		std::unique_ptr<Player> player = nullptr;

		Chest chest;

		// 
		Mesh mesh;
		std::shared_ptr<Program> program;
};

