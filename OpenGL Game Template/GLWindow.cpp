#include "GLWindow.h"

#include "Variables.h"


GLWindow::~GLWindow() {
	window.close();
}

void GLWindow::initWindow() {
	std::string title;
	sf::VideoMode windowBounds;
	sf::ContextSettings contextSettings;
	unsigned int framerateLimit;

	std::ifstream in(WINDOW_INI_CONFIG);
	if (in.is_open()) {
		std::getline(in, title);
		in >> windowBounds.width >> windowBounds.height;
		in >> framerateLimit;
		in >> contextSettings.majorVersion >> contextSettings.minorVersion;
		in >> contextSettings.depthBits;
	}
	in.close();

	// SFML
	window.create(windowBounds, title, sf::Style::Default, contextSettings);
	window.setPosition({window.getPosition().x, window.getPosition().y - 50});
	window.setFramerateLimit(framerateLimit);
	window.setActive();

	// Init GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "Glew Init Failed!\n";
		window.close();
	}

	glEnable(GL_DEPTH_TEST);

	// Set GL Viewport 
	glViewport(0, 0, getWindow().getSize().x, getWindow().getSize().y); // Lower left corner should be (0, 0);

	// Mouse (hide)
	window.setMouseCursorVisible(false);
}

void GLWindow::swapBuffers() {
	window.display();
}
