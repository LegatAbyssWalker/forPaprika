#pragma once

#include "SFML/Graphics.hpp"
#include "GL/glew.h"

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

#include "FileLocations.h"

class Texture {
	public:
		static std::shared_ptr<Texture> get(std::string name);

		Texture() : textureID(0) {}
		Texture(const std::string& fileLocation);
		~Texture();

		Texture(const Texture& tex) = delete;
		Texture& operator=(const Texture& tex) = delete;

		Texture(Texture&& tex) noexcept;
		Texture& operator=(Texture&& tex) noexcept;

		void useTexture();
		static void unbindAll();

	private:
		static std::unordered_map<std::string, std::shared_ptr<Texture>> cache;

		sf::Image image;

		GLuint textureID;

};

