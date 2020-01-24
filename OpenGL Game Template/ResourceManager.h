#pragma once

#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"

#include <iostream>

struct ResourceManager {
	TextureManager textures;
	FontManager fonts;
	SoundManager sounds;
};

