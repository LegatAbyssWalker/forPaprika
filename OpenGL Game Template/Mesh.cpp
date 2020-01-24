#include "Mesh.h"

Mesh::~Mesh() {
	clearMesh();
}

void Mesh::loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices) {
	// create a VAO
	GLuint vaoID = createVAO();
	int indicesSize = indices.size();
	bindIndicesBuffer(indices.data(), indicesSize);

	// Store the data in attribute lists
	storeDataInAttrubeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	storeDataInAttrubeList(1, 2, &textures[0], textures.size() * sizeof(glm::vec2));
	storeDataInAttrubeList(2, 3, &normals[0], normals.size() * sizeof(glm::vec3));
	unbindVAO();
}

void Mesh::renderVAO() {
	// Texture
	texture->useTexture();

	// Binding
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);

	// Rendering
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::clearMesh() {
	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}
}

GLuint Mesh::createVAO() {
	GLuint vaoID;

	glGenVertexArrays(1, &vaoID);
	VAO = vaoID;
	glBindVertexArray(vaoID);
	return vaoID;
}

void Mesh::storeDataInAttrubeList(GLuint attribNumber, int attribSize, void* data, int dataSize) {
	GLuint vboID;
	// Create a new buffer
	glGenBuffers(1, &vboID);
	// Store the buffer in the list
	VBO = vboID;
	// Bind the buffer to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// Store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, attribSize, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Mesh::bindIndicesBuffer(int* indices, int& count) {
	GLuint vboID;
	// Generate a buffer and bind it for use
	glGenBuffers(1, &vboID);
	// Store the buffer in the list
	VBO = vboID;
	// Bind the buffer to use it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	// Store the indices in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}
