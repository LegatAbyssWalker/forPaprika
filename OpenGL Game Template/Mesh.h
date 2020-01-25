#ifndef MESH_H
#define MESH_H

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Texture.h"

#include <iostream>
#include <vector>

class Mesh {
	public:
		Mesh() { VAO = 0; VBO = 0; indicesSize = 0; }
		~Mesh();


		void loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
		void loadTexture(std::shared_ptr<Texture> texture) { this->texture = texture; }
		void renderVAO();

		void clearMesh();

		inline void unbindVAO() { glBindVertexArray(0); }

	private:
		GLuint createVAO();
		void storeDataInAttrubeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
		void bindIndicesBuffer(int* indices, int& count);

		int indicesSize = 0;
		GLuint VAO = 0, VBO = 0;

		std::shared_ptr<Texture> texture;
};

#endif