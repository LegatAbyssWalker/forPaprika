#pragma once

#include "SFML/Audio.hpp"

#include <map>

enum class SoundResources {
	// Add sound types
};

class SoundManager {
	public:
		SoundManager();

		void addResource(SoundResources name, const std::string& fileLocation);
		const sf::SoundBuffer& get(SoundResources name) const { return soundMap.at(name); }

	private:

		std::map<SoundResources, sf::SoundBuffer> soundMap;
};

