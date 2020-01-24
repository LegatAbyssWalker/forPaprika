#include "TextureManager.h"

TextureManager::TextureManager() {
}

void TextureManager::addResource(TextureResources name, const std::string& fileLocation) {
	sf::Texture texture;
	texture.loadFromFile(fileLocation);

	textureMap.insert(std::make_pair(name, texture));
}
