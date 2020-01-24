#pragma once

#include "SFML/Graphics.hpp"

#include <map>

enum class FontResources {
	// Add font types
};

class FontManager {
	public:
		FontManager();

		void addResource(FontResources name, const std::string& fileLocation);
		const sf::Font& get(FontResources name) const { return fontMap.at(name); }

	private:

		std::map<FontResources, sf::Font> fontMap;
};

