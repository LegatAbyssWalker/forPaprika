#include "SoundManager.h"

SoundManager::SoundManager() {
}

void SoundManager::addResource(SoundResources name, const std::string& fileLocation) {
	sf::SoundBuffer sound;
	sound.loadFromFile(fileLocation);

	soundMap.insert(std::make_pair(name, sound));
}
