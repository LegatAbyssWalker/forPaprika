#pragma once

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <string>

class OBJLoader {
	public:
		void loadObjModel(const std::string& fileName);

		std::vector<glm::vec3> getVertices() { return vertices; }
		std::vector<glm::vec2> getTextures() { return textures; }
		std::vector<glm::vec3> getNormals() { return normals; }
		std::vector<int> getIndices() { return indices; }



	private:
		// Storing variables
		std::vector<glm::vec2> textures, tempTextures;
		std::vector<glm::vec3> vertices, normals, tempNormals;
		std::vector<int> indices;


		static void processVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures,
			std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals);
};