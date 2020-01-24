#pragma once

#include "SFML/Graphics.hpp"

#include <map>

enum class TextureResources {
	// Add texture types
};

class TextureManager {
	public:
		TextureManager();

		void addResource(TextureResources name, const std::string& fileLocation);
		const sf::Texture& get(TextureResources name) const { return textureMap.at(name); }

	private:

		std::map<TextureResources, sf::Texture> textureMap;
};

