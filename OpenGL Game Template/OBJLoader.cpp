#include "OBJLoader.h"


void OBJLoader::loadObjModel(const std::string& fileName) {
	// Opens file
	FILE* file;

	if (fopen_s(&file, fileName.c_str(), "r") != 0) {
		std::cout << "Failed to open file at: " << fileName << '\n';
	}

	char *type, *token, *stop = 0;
	double x, y, z;
	char line[256];

	while (fgets(line, 256, file) != NULL) {
		token = NULL;
		type = strtok_s(line, " ", &token);

		// Vertex
		if (type[0] == 'v' && type[1] == NULL) {
			x = strtod(token, &stop);
			token = stop + 1; 
			y = strtod(token, &stop);
			token = stop + 1; 
			z = strtod(token, &stop);
			
			vertices.push_back(glm::vec3(x, y, z));
		}

		// Textures
		else if (type[0] == 'v' && type[1] == 't') {
			x = strtod(token, &stop);
			token = stop + 1; 
			y = 1 - strtod(token, &stop);
			
			tempTextures.push_back(glm::vec2(x, y));
		}

		// Normals
		else if (type[0] == 'v' && type[1] == 'n') {
			x = strtod(token, &stop);
			token = stop + 1; 
			y = strtod(token, &stop);
			token = stop + 1; 
			z = strtod(token, &stop);
			
			tempNormals.push_back(glm::vec3(x, y, z));
		}

		// Faces
		else if (type[0] == 'f') {
			if (indices.size() == 0) {
				// Set size of the array
				textures.resize(vertices.size());
				normals.resize(vertices.size());
			}

			// Process vertices data
			processVertices(token, indices, tempTextures, textures, tempNormals, normals);
		}
	}
	fclose(file);
}

void OBJLoader::processVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures, 
	std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals) {

	char* stop;
	int vertexPointer;

	for (unsigned int i = 0; i < 3; i++) {
		// Get and store index
		vertexPointer = strtol(vertexData, &stop, 10) - 1;
		indices.push_back(vertexPointer);
		vertexData = stop + 1; 

		textures[vertexPointer] = tempTextures[strtol(vertexData, &stop, 10) - 1];
		vertexData = stop + 1; 

		normals[vertexPointer] = tempNormals[strtol(vertexData, &stop, 10) - 1];
		vertexData = stop + 1; 
	}
}
