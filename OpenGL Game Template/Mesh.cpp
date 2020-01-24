#include "Mesh.h"

Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

Mesh::~Mesh() {
	clearMesh();
}

void Mesh::loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices) {
	// Creates a VAO
	GLuint vaoID = createVAO();
	indicesSize = indices.size();
	bindIndicesBuffer(indices.data(), indicesSize);

	// Store data in attrib list
	storeDataInAttrubeList(0, 3, &vertices[0], vertices.size() * sizeof(glm::vec3));
	storeDataInAttrubeList(1, 2, &textures[0], textures.size() * sizeof(glm::vec2));
	storeDataInAttrubeList(2, 3, &normals[0],  normals.size()  * sizeof(glm::vec3));
	unbindVAO();

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Mesh::renderVAO() {
	// Binding
	glBindVertexArray(vaos);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos);

	// Rendering
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);

	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::createMesh(const std::vector<GLfloat>& vertices) {
	this->vertices = vertices;

	// Binding
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Information
	// VBO Information
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size(), vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, (void*)(sizeof(GLuint) * 3));
	glEnableVertexAttribArray(1);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
	indexCount = indices.size();

	// Binding
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Information
	// VBO Information
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// IBO Information
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, (void*)(sizeof(GLuint) * 3));
	glEnableVertexAttribArray(1);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh() {
	// Binding
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Rendering
	if (indexCount > 0) { glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0); }
	else { glDrawArrays(GL_TRIANGLES, 0, vertices.size()); }

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

	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	indexCount = 0;
}

GLuint Mesh::createVAO() {
	GLuint vaoID;

	glGenVertexArrays(1, &vaoID);
	vaos = vaoID;
	glBindVertexArray(vaoID);
	return vaoID;
}

void Mesh::storeDataInAttrubeList(GLuint attribNumber, int attribSize, void* data, int dataSize) {
	GLuint vboID;
	// Create a new buffer
	glGenBuffers(1, &vboID);
	// Store the buffer in the list
	vbos = vboID;
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
	vbos = vbos;
	// Bind the buffer to use it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	// Store the indices in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}
