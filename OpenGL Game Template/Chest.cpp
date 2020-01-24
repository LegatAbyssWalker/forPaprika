#include "Chest.h"

Chest::Chest(GLWindow& window)
	: mesh(), window(window) {


	objLoader.loadObjModel("res/models/chest.obj");

	mesh.loadToVAO(objLoader.getVertices(), objLoader.getTextures(), objLoader.getNormals(), objLoader.getIndices());
	program = Program::get(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER);
}

void Chest::setPosition(glm::vec3 position) {
	this->position = position;
}

void Chest::update() {
	// ?
}

void Chest::render(const glm::mat4 viewMatrix, const glm::mat4 projection) {
	program->useProgram();

	// Model matrix
	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	model = glm::scale(model, scaleValue);

	// View matrix
	glm::mat4 view = viewMatrix;

	// Uniforms
	program->setMat4("model", model);
	program->setMat4("view", view);
	program->setMat4("projection", projection);

	// Rendering
	mesh.renderMesh();
}
