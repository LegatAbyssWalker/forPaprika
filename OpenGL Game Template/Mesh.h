#ifndef MESH_H
#define MESH_H

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Texture.h"

#include <iostream>
#include <vector>

class Mesh {
	public:
		Mesh();
		~Mesh();


		void loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
		void renderVAO();

		void createMesh(const std::vector<GLfloat>& vertices);
		void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
		void renderMesh();

		void clearMesh();

		inline void unbindVAO() { glBindVertexArray(0); }

	private:
		GLuint createVAO();
		void storeDataInAttrubeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
		void bindIndicesBuffer(int* indices, int& count);

		std::vector<GLfloat> vertices;
		int indicesSize;
		GLuint vaos, vbos;

		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
};

#endif