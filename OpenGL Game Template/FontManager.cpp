#include "FontManager.h"

FontManager::FontManager() {
}

void FontManager::addResource(FontResources name, const std::string& fileLocation) {
	sf::Font font;
	font.loadFromFile(fileLocation);

	fontMap.insert(std::make_pair(name, font));
}
