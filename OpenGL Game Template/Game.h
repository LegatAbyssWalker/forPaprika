#pragma once

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "PlayingState.h"

class Game {
	public:
		Game() = default;

		void run();

	private:
		std::unique_ptr<GLWindow> window;
		StateMachine machine;
};

